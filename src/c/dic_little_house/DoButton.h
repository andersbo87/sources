//
//  DoButton.h
//  dic_little_house
//
//  Created by Anders Bolt-Evensen on 12/30/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
//#import <mysql.h>
@interface DoButton : NSButtonCell {
	IBOutlet NSTextField *textField1;
	IBOutlet NSTextField *textField2;
}
- (IBAction)doSomething:(id)pId;
@end
