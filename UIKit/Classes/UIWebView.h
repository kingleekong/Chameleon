/*
 * Copyright (c) 2011, The Iconfactory. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of The Iconfactory nor the names of its contributors may
 *    be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE ICONFACTORY BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#import "UIView.h"
#import "UIDataDetectors.h"

enum {
	UIWebViewNavigationTypeLinkClicked,
	UIWebViewNavigationTypeFormSubmitted,
	UIWebViewNavigationTypeBackForward,
	UIWebViewNavigationTypeReload,
	UIWebViewNavigationTypeFormResubmitted,
	UIWebViewNavigationTypeOther
};
typedef NSUInteger UIWebViewNavigationType;

@class UIWebView, UIViewAdapter, WebView;

@protocol UIWebViewDelegate <NSObject>
@optional
- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType;
- (void)webView:(UIWebView *)aWebView didFailLoadWithError:(NSError *)error;
@end

@interface UIWebView : UIView {
@private
	id _delegate;
	NSURLRequest *_request;
	UIDataDetectorTypes _dataDetectorTypes;
	WebView *_webView;
	UIViewAdapter *_webViewAdapter;
    BOOL _scalesPageToFit;
	
	struct {
		BOOL shouldStartLoadWithRequest : 1;
		BOOL didFailLoadWithError : 1;
	} _delegateHas;
}

- (void)loadHTMLString:(NSString *)string baseURL:(NSURL *)baseURL;
- (void)loadRequest:(NSURLRequest *)request;
- (void)stopLoading;
- (void)reload;
- (void)goBack;
- (void)goForward;

- (NSString *)stringByEvaluatingJavaScriptFromString:(NSString *)script;

@property (nonatomic, assign) id<UIWebViewDelegate> delegate;
@property (nonatomic, readonly, getter=isLoading) BOOL loading;
@property (nonatomic, readonly, getter=canGoBack) BOOL canGoBack;
@property (nonatomic, readonly, getter=canGoForward) BOOL canGoForward;
@property (nonatomic, assign) BOOL scalesPageToFit; // not implemented
@property (nonatomic, readonly, retain) NSURLRequest *request;
@property (nonatomic) UIDataDetectorTypes dataDetectorTypes;

@end
