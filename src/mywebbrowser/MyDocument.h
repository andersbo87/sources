//
//  MyDocument.h
//  mywebbrowser
//
//  Created by Anders Bolt-Evensen on 9/17/10.
//  Copyright 2010 Høgskolen i Østfold. All rights reserved.
//


#import <Cocoa/Cocoa.h>
#import <WebKit/WebKit.h>


@interface MyDocument : NSDocument
{
	IBOutlet id urlString;
	IBOutlet WebView *webView;
}
-(IBAction)connectURL:(id)sender;
@end
