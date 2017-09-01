//
//  MyDocument.h
//  Skriv
//
//  Created by Anders Bolt-Evensen on 12/31/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//


#import <Cocoa/Cocoa.h>

@interface MyDocument : NSDocument
{
	IBOutlet NSTextView *textView;
    NSAttributedString *mString;
}
- (NSAttributedString *) string;
- (void) setString: (NSAttributedString *) value;

@end
