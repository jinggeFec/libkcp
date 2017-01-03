//
// Created by 理 傅 on 2017/1/1.
//

#ifndef KCP_REEDSOLOMON_H
#define KCP_REEDSOLOMON_H

#include "matrix.h"
#include "inversion_tree.h"

class ReedSolomon {
public:
    ReedSolomon(const ReedSolomon &) = delete;
    ReedSolomon &operator=(const ReedSolomon &) = delete;

    // New creates a new encoder and initializes it to
    // the number of data shards and parity shards that
    // you want to use. You can reuse this encoder.
    // Note that the maximum number of data shards is 256.
    static ReedSolomon * New(int dataShards, int parityShards);

    // Encodes parity for a set of data shards.
    // An array 'shards' containing data shards followed by parity shards.
    // The number of shards must match the number given to New.
    // Each shard is a byte array, and they must all be the same size.
    // The parity shards will always be overwritten and the data shards
    // will remain the same.
    int Encode(char**shards, int dataShards, size_t shardSize);

    // Multiplies a subset of rows from a coding matrix by a full set of
    // input shards to produce some output shards.
    // 'matrixRows' is The rows from the matrix to use.
    // 'inputs' An array of byte arrays, each of which is one input shard.
    // The number of inputs used is determined by the length of each matrix row.
    // outputs Byte arrays where the computed shards are stored.
    // The number of outputs computed, and the
    // number of matrix rows used, is determined by
    // outputCount, which is the number of outputs to compute.
    void codeSomeShards(char **matrixRows, char ** inputs, char **outputs, int outputCount, size_t byteCount);

    // Reconstruct will recreate the missing shards, if possible.
    //
    // Given a list of shards, some of which contain data, fills in the
    // ones that don't have data.
    //
    // The length of the array must be equal to Shards.
    // You indicate that a shard is missing by setting it to nil.
    //
    // If there are too few shards to reconstruct the missing
    // ones, ErrTooFewShards will be returned.
    //
    // The reconstructed shard set is complete, but integrity is not verified.
    // Use the Verify function to check if data set is ok.
    int Reconstruct(char ** shards, size_t numShards, size_t shardSize);

private:
    int DataShards;  // Number of data shards, should not be modified.
    int ParityShards; // Number of parity shards, should not be modified.
    int Shards; // Total number of shards. Calculated, and should not be modified.

    matrix *m;
    inversionTree *tree;
    char **parity;

    ReedSolomon() = default;
    ~ReedSolomon() = default;
};



#endif //KCP_REEDSOLOMON_H