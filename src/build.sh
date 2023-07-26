#!/bin/bash

if [[ "$#" -lt 2 ]]; then
  echo "Usage ./build <program> <input> [ll/bc] (default: ll)"
  exit 1
fi

set -x

FILE=$1
FILENAME=${FILE%%.*}
EXT=${FILE##*.}
INPUT_JSON=$2

LLVM_EXT=
LLVM_OUT=
STD=

if [[ "$#" -eq 4 ]]; then
  LLVM_EXT=$3
else
  LLVM_EXT=ll
fi

if [[ "$LLVM_EXT" == "ll" ]]; then
  LLVM_OUT=-S
else
  LLVM_OUT=-c
fi

if [[ "$EXT" == "cpp" ]]; then
  STD="c++20"
else
  STD="c99"
fi

SCRIPT_PROOF_MARKET_DIR=/home/robertorosmaninho/rv/zk-experiments/proof-market-toolchain/scripts
PROOF_GENERATOR_DIR=/home/robertorosmaninho/rv/zk-experiments/proof-market-toolchain/build/bin/proof-generator
ZKL_LLVM_DIR=/home/robertorosmaninho/rv/zk-experiments/zkllvm
CRYPTO3_LIB_DIR=${ZKL_LLVM_DIR}/libs/crypto3
CLANG_EXE=${ZKL_LLVM_DIR}/build/libs/circifier/llvm/bin/clang-16
BOOST_1_82_0_DIR=/home/robertorosmaninho/rv/boost_1_82_0

${CLANG_EXE} -target assigner -Xclang -no-opaque-pointers -Xclang -fpreserve-vec3-type -std="${STD}"     -D__ZKLLVM__ \
-I ${CRYPTO3_LIB_DIR}/algebra/include \
-I ${ZKL_LLVM_DIR}/build/include \
-I ${BOOST_1_82_0_DIR}/build/include \
-I ${CRYPTO3_LIB_DIR}/block/include \
-I ${BOOST_1_82_0_DIR}/build/include \
-I ${ZKL_LLVM_DIR}/libs/blueprint/include \
-I ${CRYPTO3_LIB_DIR}/codec/include \
-I ${CRYPTO3_LIB_DIR}/containers/include \
-I ${CRYPTO3_LIB_DIR}/hash/include \
-I ${CRYPTO3_LIB_DIR}/kdf/include \
-I ${CRYPTO3_LIB_DIR}/mac/include \
-I ${CRYPTO3_LIB_DIR}/marshalling/core/include \
-I ${CRYPTO3_LIB_DIR}/marshalling/algebra/include \
-I ${CRYPTO3_LIB_DIR}/marshalling/multiprecision/include \
-I ${CRYPTO3_LIB_DIR}/marshalling/zk/include \
-I ${CRYPTO3_LIB_DIR}/math/include \
-I ${CRYPTO3_LIB_DIR}/modes/include \
-I ${CRYPTO3_LIB_DIR}/multiprecision/include \
-I ${CRYPTO3_LIB_DIR}/passhash/include \
-I ${CRYPTO3_LIB_DIR}/pbkdf/include \
-I ${CRYPTO3_LIB_DIR}/pkmodes/include \
-I ${CRYPTO3_LIB_DIR}/pkpad/include \
-I ${CRYPTO3_LIB_DIR}/pubkey/include \
-I ${CRYPTO3_LIB_DIR}/random/include \
-I ${CRYPTO3_LIB_DIR}/stream/include \
-I ${CRYPTO3_LIB_DIR}/vdf/include \
-I ${CRYPTO3_LIB_DIR}/zk/include \
-I ${ZKL_LLVM_DIR}/libs/stdlib/libcpp \
-I ${ZKL_LLVM_DIR}/libs/stdlib/libc/include \
-emit-llvm -O1 "${LLVM_OUT}" "${FILE}" -O3 -funroll-loops -finline-functions -fomit-frame-pointer -Wall -pedantic \
-Wno-unused-but-set-variable -Wno-misleading-indentation -Wno-writable-strings


python ${SCRIPT_PROOF_MARKET_DIR}/prepare_statement.py -c="${FILENAME}.${LLVM_EXT}" -o=metamath_statement.json -n=metamath -t=placeholder-zkllvm
${PROOF_GENERATOR_DIR}/proof-generator --proof_out=metamath_output.bin --circuit_input=metamath_statement.json --public_input="${INPUT_JSON}"
