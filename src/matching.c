#include "matching.h"

MatchType match_type(const Matching match)
{
    if (!match.match) {
        return NONE;
    } else if (!match.rest) {
        return EXACT;
    } else {
        return PARTIAL;
    }
}
