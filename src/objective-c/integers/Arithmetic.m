#import "Arithmetic.h"

@implementation Integer (Arithmetic)
- (id) add: (Integer *) addend {
        return [self integer: [self integer] + [addend integer]];
}
- (id) sub: (Integer *) subtrahend {
        return [self integer: [self integer] - [subtrahend integer]];
}
@end
