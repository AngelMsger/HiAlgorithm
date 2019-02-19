#ifndef HIALGORITHM_DAG_H
#define HIALGORITHM_DAG_H

#include "base.h"

namespace angelmsger {
template <typename K, typename V>
struct DAGNode {
    K key;
    V val;
};

class DAG {};
}  // namespace angelmsger

#endif  // HIALGORITHM_DAG_H
