#include <bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;

using pref_trie = trie<string, null_type, trie_string_access_traits<>,
                       pat_trie_tag, trie_prefix_search_node_update>;
