
#ifndef SUFFIX_TRIES_H
#define SUFFIX_TRIES_H

// Let T be a string
// A suffix trie of T is defined as STrie(T) = (Q, root, F, g, f)
// where Q includes bottom
//
// Such a trie is an augmented deterministic finite-state automation which has
// a tree-shaped transition graph representing the trie for all suffixes and
// which is augmented with the so called suffix function f and the auxillary
// state bottom.
//
// The set Q of the possible states can be put in a one-to-one correspondence
// with the substrings of T. We denote by /x the state that corresponds to a
// substring x.
//
// The initial root state corresponds to the empty string and the set F of the
// final states corresponds to all suffixes of T.
//
// The transition function g is defined as g(/x, a) = /y for all /x, /y in Q
// such that y is 1 character longer than x.
//
// The suffix function is defined for each state /x in Q as follows:
//
// Let /x != root. Then x = ay for some character a and we set f(/x) = /y.
// Moreover f(root) = bottom.
//
// The auxillary state bottom allows us to write the algorithms such that an
// explicit distiction between empty and non-empty suffixes can be avoided
//
// State Bottom is connected to the trie by g(bottom, a) = root for every
// character a.
//
// We leave f(bottom) undefined.
//
// f(r) is called the suffix link of state r. The suffix links are utilized
// during the cunstruction of a suffix tree.
//
// It is easy to construct STrie(T) on line in a left-to right scan over T.
//
// The key observation is explaining how STrie(Ti) is obtained from
// STrie(Ti-1):
// The suffixes of Ti can be obtained by catenating T[i] to the end of each
// suffix of Ti-1 and adding an empty suffix.
//
//
// By definition STrie(Ti-1) accepts all suffixes of Ti-1. To make it accept
// all suffixes of Ti, wo look at the final state set Fi-1 of STrie(Ti-1). If
// some of these final states not already has a T[i] transition, then such a
// transition from r (that becomes a leaf of the trie) is added. The added
// states together with the old constitute the final states of Ti.
//
// The final states of Ti-1 that get new transitions can be found using the
// suffix links as follows.
//
// By the difinition of suffix link implies that some state is final iff
// f_j(/T[1]..T[i-1]) for some j less than i-1. Therefore, all final states are
// on the path of suffix links that starts from the deepest state /T[1]..T[i-1]
// and ends at bottom. We call this the boundry path.
//
// The boundry path is traversed. If a state /z on the bondry path does not
// have a transition on T[i} yet:
// a new state /zT[i] and
// a new transition g(/z, T[i]) = /zT[i] are added
//
// This updates g. To update f, the new states /zT[i] are linked together with
// new suffix links that perform a path starting from /T[1]..T[i].
// This is the boundry path of STrie(Ti)
//
// Tre traversal over the final states of Ti-1 along the boundry path can be
// stopped immediately the first state /z is found such that /zT[i] already
// exists.
//
// When the traversal is stopped in this way, the procedure creates a new state
// for every suffix link examined during th etraversal. This implies that the
// whole procedure takes time proportional to the size of the resulting
// automaton.
//
// In the following summary of the algorithm, top denotes /T[1]..t[i-1]
//
// Algorithm 1
//
//  r <- top
//  while g(r, T[i]) is undefined do
//      create new state r' and new transition g(r, T[i]) = r'
//      if r != top then crete new suffix link f(oldr') = r'
//      oldr' <- r'
//      r <- f(r)
//  create new suffix link f(oldr') = g(r, T[i])
//  top <- g(top, T[i])


#endif
