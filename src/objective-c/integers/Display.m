#import <stdio.h>
#import "Display.h"

@implementation Integer (Display)
- (id) showstars{
        int i, x = [self integer];
        for (i=0; i < x; i++)
        {
                fprintf(stdout, "*");
        }
        fprintf(stdout, "*");
        return self;
}
- (id) showint {
  fprintf(stdout, "%d\n", [self integer]);
        return self;
}
@end
