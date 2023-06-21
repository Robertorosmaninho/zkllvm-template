#!/usr/bin/env bash
set -euo pipefail

# define dirs so that we can run scripts from any directory without shifting filesystem paths
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
REPO_ROOT="$SCRIPT_DIR/.."

# podman is a safer option for using on CI machines
if ! command -v podman; then
    DOCKER="docker"
    DOCKER_OPTS=""
else
    DOCKER="podman"
    DOCKER_OPTS='--detach-keys= --userns=keep-id'
fi

RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color
# checking files that should be produced
# on all steps of the pipeline
check_file_exists() {
    FILE1="${1}"
    if [ ! -e "$FILE1" ]
    then
        echo -e "${RED}File $FILE1 was not created\n ${NC}" >&2
        exit 1
    else
        echo -e "File $FILE1 created successfully\n"
       # ls -hal "$FILE1"
    fi
}

# Compile source code into a circuit
compile() {
    example_name=$1
    echo "Compiling $example_name"
    if [ "$USE_DOCKER" = true ] ; then
        cd "$REPO_ROOT"
        $DOCKER run $DOCKER_OPTS \
          --rm \
          --platform=linux/amd64 \
          --user $(id -u ${USER}):$(id -g ${USER}) \
          --volume $(pwd):/opt/zkllvm-template \
          ghcr.io/nilfoundation/zkllvm-template:latest \
          sh -c "bash ./scripts/ci.sh compile $example_name"
        cd -
    else
        rm -rf "$REPO_ROOT/build"
        mkdir -p "$REPO_ROOT/build"
        cd "$REPO_ROOT/build"
        cmake -DCIRCUIT_ASSEMBLY_OUTPUT=TRUE ..
        make "$example_name"
        cd -
        cp "$REPO_ROOT/src/$example_name/${example_name}_input.json"  "$REPO_ROOT/build/src/$example_name/"
        check_file_exists "$REPO_ROOT/build/src/$example_name/$example_name.ll"
    fi
}

# Use assigner to produce a constraint file and an assignment table.
# This is not a part of the basic development workflow,
# but can be used for debugging circuits.
run_assigner() {
    if [ "$USE_DOCKER" = true ] ; then
        cd "$REPO_ROOT"
        $DOCKER run $DOCKER_OPTS \
          --rm \
          --platform=linux/amd64 \
          --user $(id -u ${USER}):$(id -g ${USER}) \
          --volume $(pwd):/opt/zkllvm-template \
          ghcr.io/nilfoundation/zkllvm-template:latest \
          sh -c "bash ./scripts/ci.sh run_assigner"
        cd -
    else
        cd "$REPO_ROOT/build"
        assigner \
          -b src/template.ll \
          -i ../src/main.inp \
          -c template.crct \
          -t template.tbl \
          -e pallas
        cd -
        check_file_exists "$REPO_ROOT/build/template.crct"
        check_file_exists "$REPO_ROOT/build/template.tbl"
    fi
}

# Use the Proof Market toolchain to pack circuit into a statement
# that can later be used to produce a proof locally or sent to the
# Proof Market.
build_statement() {
    example_name=$1
    echo "Building statement $example_name"
    if [ "$USE_DOCKER" = true ] ; then
        cd "$REPO_ROOT"
        $DOCKER run $DOCKER_OPTS \
          --rm \
          --platform=linux/amd64 \
          --user $(id -u ${USER}):$(id -g ${USER}) \
          --volume $(pwd):/opt/zkllvm-template \
          ghcr.io/nilfoundation/proof-market-toolchain:latest \
          sh -c "bash /opt/zkllvm-template/scripts/ci.sh build_statement $example_name"
        cd -
    else
        python3 /proof-market-toolchain/scripts/prepare_statement.py \
            --circuit "$REPO_ROOT/build/src/$example_name/$example_name.ll" \
            --name template --type placeholder-zkllvm \
            --output "$REPO_ROOT/build/src/$example_name/$example_name.json"
        check_file_exists "$REPO_ROOT/build/src/$example_name/$example_name.json"
    fi
}

# Prove the circuit with particular input.
# See the input files at:
# ./src/main.inp
# ./src/main-input.json
prove() {
    example_name=$1
    echo "Proving $example_name"
    echo -e "${BLUE}"
    if [ "$USE_DOCKER" = true ] ; then
        cd "$REPO_ROOT"
        $DOCKER run $DOCKER_OPTS \
          --rm \
          --platform=linux/amd64 \
          --user $(id -u ${USER}):$(id -g ${USER}) \
          --volume $(pwd):/opt/zkllvm-template \
          ghcr.io/nilfoundation/proof-market-toolchain:latest \
          sh -c "bash /opt/zkllvm-template/scripts/ci.sh prove $example_name"
        cd -
    else
        mkdir -p .config
        touch .config/config.ini
        proof-generator \
            --circuit_input="$REPO_ROOT/build/src/$example_name/$example_name.json" \
            --public_input="$REPO_ROOT/build/src/$example_name/${example_name}_input.json" \
            --proof_out="$REPO_ROOT/build/src/$example_name/$example_name.proof"
        echo -e "${NC}"
        check_file_exists "$REPO_ROOT/build/src/$example_name/$example_name.proof"
    fi
}

run_all() {
    compile "$@"
    #run_assigner
    build_statement "$@"
    prove "$@"
}

USE_DOCKER=false
SUBCOMMAND=run_all

while [[ "$#" -gt 0 ]]; do
    case $1 in
        -d|--docker) USE_DOCKER=true ;;
        all)
            SUBCOMMAND=run_all
            shift
            break
            ;;
        compile)
            SUBCOMMAND=compile
            shift
            break
            ;;
        run_assigner) SUBCOMMAND=run_assigner ;;
        build_statement)
            SUBCOMMAND=build_statement
            shift
            break
            ;;
        prove)
            SUBCOMMAND=prove
            shift
            break
            ;;
        *) echo "Unknown parameter passed: $1"; exit 1 ;;
    esac
    shift
done

echo "Running ${SUBCOMMAND}"
$SUBCOMMAND "$@"
