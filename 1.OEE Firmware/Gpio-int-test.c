<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html dir="ltr" lang="en"><head>
<title>Gpio-int-test.c - RidgeRun Developer Connection</title>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<meta name="generator" content="MediaWiki 1.16.0beta2">
<link rel="shortcut icon" href="https://developer.ridgerun.com/wiki/skins/common/images/favicon.ico">
<link rel="search" type="application/opensearchdescription+xml" href="https://developer.ridgerun.com/wiki/opensearch_desc.php" title="RidgeRun Developer Connection (en)">
<link rel="alternate" type="application/atom+xml" title="RidgeRun Developer Connection Atom feed" href="https://developer.ridgerun.com/wiki/index.php?title=Special:RecentChanges&amp;feed=atom">
<link rel="stylesheet" href="Gpio-int-test_files/main-ltr.css" media="screen">
<link rel="stylesheet" href="Gpio-int-test_files/shared.css" media="screen">
<link rel="stylesheet" href="Gpio-int-test_files/commonPrint.css" media="print">
<link rel="stylesheet" href="Gpio-int-test_files/index_004.css">
<link rel="stylesheet" href="Gpio-int-test_files/index_002.css" media="print">
<link rel="stylesheet" href="Gpio-int-test_files/index.css">
<link rel="stylesheet" href="Gpio-int-test_files/index_003.css">
<script>
var skin="vector",
stylepath="/wiki/skins",
wgUrlProtocols="http\\:\\/\\/|https\\:\\/\\/|ftp\\:\\/\\/|irc\\:\\/\\/|gopher\\:\\/\\/|telnet\\:\\/\\/|nntp\\:\\/\\/|worldwind\\:\\/\\/|mailto\\:|news\\:|svn\\:\\/\\/",
wgArticlePath="/wiki/index.php/$1",
wgScriptPath="/wiki",
wgScriptExtension=".php",
wgScript="/wiki/index.php",
wgVariantArticlePath=false,
wgActionPaths={},
wgServer="https://developer.ridgerun.com",
wgCanonicalNamespace="",
wgCanonicalSpecialPageName=false,
wgNamespaceNumber=0,
wgPageName="Gpio-int-test.c",
wgTitle="Gpio-int-test.c",
wgAction="view",
wgArticleId=236,
wgIsArticle=true,
wgUserName=null,
wgUserGroups=null,
wgUserLanguage="en",
wgContentLanguage="en",
wgBreakFrames=false,
wgCurRevisionId=2604,
wgVersion="1.16.0beta2",
wgEnableAPI=true,
wgEnableWriteAPI=true,
wgSeparatorTransformTable=["", ""],
wgDigitTransformTable=["", ""],
wgMainPageTitle="Main Page",
wgFormattedNamespaces={"-2": "Media", "-1": "Special", "0": "", "1": "Talk", "2": "User", "3": "User talk", "4": "RidgeRun Developer Connection", "5": "RidgeRun Developer Connection talk", "6": "File", "7": "File talk", "8": "MediaWiki", "9": "MediaWiki talk", "10": "Template", "11": "Template talk", "12": "Help", "13": "Help talk", "14": "Category", "15": "Category talk"},
wgNamespaceIds={"media": -2, "special": -1, "": 0, "talk": 1, "user": 2, "user_talk": 3, "ridgerun_developer_connection": 4, "ridgerun_developer_connection_talk": 5, "file": 6, "file_talk": 7, "mediawiki": 8, "mediawiki_talk": 9, "template": 10, "template_talk": 11, "help": 12, "help_talk": 13, "category": 14, "category_talk": 15, "image": 6, "image_talk": 7},
wgSiteName="RidgeRun Developer Connection",
wgCategories=[],
wgRestrictionEdit=[],
wgRestrictionMove=[];
</script><script src="Gpio-int-test_files/wikibits.js"></script>
<script src="Gpio-int-test_files/ajax.js"></script>
<!--[if lt IE 7]><style type="text/css">body{behavior:url("/wiki/skins/vector/csshover.htc")}</style><![endif]-->
<script src="Gpio-int-test_files/index.php"></script>

</head>
<body class="mediawiki ltr ns-0 ns-subject page-Gpio-int-test_c skin-vector">
		<div id="page-base" class="noprint"></div>
		<div id="head-base" class="noprint"></div>
		<!-- content -->
		<div id="content">
			<a id="top"></a>
			<div id="mw-js-message" style="display:none;"></div>
						<!-- firstHeading -->
			<h1 id="firstHeading" class="firstHeading">Gpio-int-test.c</h1>
			<!-- /firstHeading -->
			<!-- bodyContent -->
			<div id="bodyContent">
				<!-- tagline -->
				<h3 id="siteSub">From RidgeRun Developer Connection</h3>
				<!-- /tagline -->
				<!-- subtitle -->
				<div id="contentSub"></div>
				<!-- /subtitle -->
																<!-- jumpto -->
				<div id="jump-to-nav">
					Jump to:<a href="#head">navigation</a>,
					<a href="#p-search">search</a>
				</div>
				<!-- /jumpto -->
								<!-- bodytext -->
				<pre>/* Copyright (c) 2011, RidgeRun
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    This product includes software developed by the RidgeRun.
 * 4. Neither the name of the RidgeRun nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY RIDGERUN ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL RIDGERUN BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;
#include &lt;errno.h&gt;
#include &lt;unistd.h&gt;
#include &lt;fcntl.h&gt;
#include &lt;poll.h&gt;

 /****************************************************************
 * Constants
 ****************************************************************/
 
#define SYSFS_GPIO_DIR "/sys/class/gpio"
#define POLL_TIMEOUT (3 * 1000) /* 3 seconds */
#define MAX_BUF 64

/****************************************************************
 * gpio_export
 ****************************************************************/
int gpio_export(unsigned int gpio)
{
	int fd, len;
	char buf[MAX_BUF];
 
	fd = open(SYSFS_GPIO_DIR "/export", O_WRONLY);
	if (fd &lt; 0) {
		perror("gpio/export");
		return fd;
	}
 
	len = snprintf(buf, sizeof(buf), "%d", gpio);
	write(fd, buf, len);
	close(fd);
 
	return 0;
}

/****************************************************************
 * gpio_unexport
 ****************************************************************/
int gpio_unexport(unsigned int gpio)
{
	int fd, len;
	char buf[MAX_BUF];
 
	fd = open(SYSFS_GPIO_DIR "/unexport", O_WRONLY);
	if (fd &lt; 0) {
		perror("gpio/export");
		return fd;
	}
 
	len = snprintf(buf, sizeof(buf), "%d", gpio);
	write(fd, buf, len);
	close(fd);
	return 0;
}

/****************************************************************
 * gpio_set_dir
 ****************************************************************/
int gpio_set_dir(unsigned int gpio, unsigned int out_flag)
{
	int fd, len;
	char buf[MAX_BUF];
 
	len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR  "/gpio%d/direction", gpio);
 
	fd = open(buf, O_WRONLY);
	if (fd &lt; 0) {
		perror("gpio/direction");
		return fd;
	}
 
	if (out_flag)
		write(fd, "out", 4);
	else
		write(fd, "in", 3);
 
	close(fd);
	return 0;
}

/****************************************************************
 * gpio_set_value
 ****************************************************************/
int gpio_set_value(unsigned int gpio, unsigned int value)
{
	int fd, len;
	char buf[MAX_BUF];
 
	len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);
 
	fd = open(buf, O_WRONLY);
	if (fd &lt; 0) {
		perror("gpio/set-value");
		return fd;
	}
 
	if (value)
		write(fd, "1", 2);
	else
		write(fd, "0", 2);
 
	close(fd);
	return 0;
}

/****************************************************************
 * gpio_get_value
 ****************************************************************/
int gpio_get_value(unsigned int gpio, unsigned int *value)
{
	int fd, len;
	char buf[MAX_BUF];
	char ch;

	len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);
 
	fd = open(buf, O_RDONLY);
	if (fd &lt; 0) {
		perror("gpio/get-value");
		return fd;
	}
 
	read(fd, &amp;ch, 1);

	if (ch&nbsp;!= '0') {
		*value = 1;
	} else {
		*value = 0;
	}
 
	close(fd);
	return 0;
}


/****************************************************************
 * gpio_set_edge
 ****************************************************************/

int gpio_set_edge(unsigned int gpio, char *edge)
{
	int fd, len;
	char buf[MAX_BUF];

	len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/edge", gpio);
 
	fd = open(buf, O_WRONLY);
	if (fd &lt; 0) {
		perror("gpio/set-edge");
		return fd;
	}
 
	write(fd, edge, strlen(edge) + 1); 
	close(fd);
	return 0;
}

/****************************************************************
 * gpio_fd_open
 ****************************************************************/

int gpio_fd_open(unsigned int gpio)
{
	int fd, len;
	char buf[MAX_BUF];

	len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);
 
	fd = open(buf, O_RDONLY | O_NONBLOCK );
	if (fd &lt; 0) {
		perror("gpio/fd_open");
	}
	return fd;
}

/****************************************************************
 * gpio_fd_close
 ****************************************************************/

int gpio_fd_close(int fd)
{
	return close(fd);
}

/****************************************************************
 * Main
 ****************************************************************/
int main(int argc, char **argv, char **envp)
{
	struct pollfd fdset[2];
	int nfds = 2;
	int gpio_fd, timeout, rc;
	char *buf[MAX_BUF];
	unsigned int gpio;
	int len;



	if (argc &lt; 2) {
		printf("Usage: gpio-int &lt;gpio-pin&gt;\n\n");
		printf("Waits for a change in the GPIO pin voltage level or input on stdin\n");
		exit(-1);
	}

	gpio = atoi(argv[1]);

	gpio_export(gpio);
	gpio_set_dir(gpio, 0);
	gpio_set_edge(gpio, "rising");
	gpio_fd = gpio_fd_open(gpio);

	timeout = POLL_TIMEOUT;
 
	while (1) {
		memset((void*)fdset, 0, sizeof(fdset));

		fdset[0].fd = STDIN_FILENO;
		fdset[0].events = POLLIN;
      
		fdset[1].fd = gpio_fd;
		fdset[1].events = POLLPRI;

		rc = poll(fdset, nfds, timeout);      

		if (rc &lt; 0) {
			printf("\npoll() failed!\n");
			return -1;
		}
      
		if (rc == 0) {
			printf(".");
		}
            
		if (fdset[1].revents &amp; POLLPRI) {
			len = read(fdset[1].fd, buf, MAX_BUF);
			printf("\npoll() GPIO&nbsp;%d interrupt occurred\n", gpio);
		}

		if (fdset[0].revents &amp; POLLIN) {
			(void)read(fdset[0].fd, buf, 1);
			printf("\npoll() stdin read 0x%2.2X\n", (unsigned int) buf[0]);
		}

		fflush(stdout);
	}

	gpio_fd_close(gpio_fd);
	return 0;
}
</pre>

<!-- 
NewPP limit report
Preprocessor node count: 4/1000000
Post-expand include size: 0/2097152 bytes
Template argument size: 0/2097152 bytes
Expensive parser function count: 0/100
-->

<!-- Saved in parser cache with key devwikidb:pcache:idhash:236-0!1!0!!en!2!edit=0 and timestamp 20140306153846 -->
<div class="printfooter">
Retrieved from "<a href="https://developer.ridgerun.com/wiki/index.php/Gpio-int-test.c">https://developer.ridgerun.com/wiki/index.php/Gpio-int-test.c</a>"</div>
				<!-- /bodytext -->
								<!-- catlinks -->
				<div id="catlinks" class="catlinks catlinks-allhidden"></div>				<!-- /catlinks -->
												<div class="visualClear"></div>
			</div>
			<!-- /bodyContent -->
		</div>
		<!-- /content -->
		<!-- header -->
		<div id="head" class="noprint">
			
<!-- 0 -->
<div id="p-personal" class="">
	<h5>Personal tools</h5>
	<ul>
					<li id="pt-login"><a href="https://developer.ridgerun.com/wiki/index.php?title=Special:UserLogin&amp;returnto=Gpio-int-test.c" title="You are encouraged to log in; however, it is not mandatory [alt-o]" accesskey="o">Log in</a></li>
			</ul>
</div>

<!-- /0 -->
			<div id="left-navigation">
				
<!-- 0 -->
<div id="p-namespaces" class="vectorTabs">
	<h5>Namespaces</h5>
	<ul>
					<li id="ca-nstab-main" class="selected"><a href="https://developer.ridgerun.com/wiki/index.php/Gpio-int-test.c" title="View the content page [alt-c]" accesskey="c"><span>Page</span></a></li>
					<li id="ca-talk" class="new"><a href="https://developer.ridgerun.com/wiki/index.php?title=Talk:Gpio-int-test.c&amp;action=edit&amp;redlink=1" title="Discussion about the content page [alt-t]" accesskey="t"><span>Discussion</span></a></li>
			</ul>
</div>

<!-- /0 -->

<!-- 1 -->
<div id="p-variants" class="vectorMenu emptyPortlet">
	<h5><span>Variants</span><a href="#"></a></h5>
	<div class="menu">
		<ul>
					</ul>
	</div>
</div>

<!-- /1 -->
			</div>
			<div id="right-navigation">
				
<!-- 0 -->
<div id="p-views" class="vectorTabs">
	<h5>Views</h5>
	<ul>
					<li id="ca-view" class="selected"><a href="https://developer.ridgerun.com/wiki/index.php/Gpio-int-test.c"><span>Read</span></a></li>
					<li id="ca-viewsource"><a href="https://developer.ridgerun.com/wiki/index.php?title=Gpio-int-test.c&amp;action=edit" title="This page is protected.
You can view its source [alt-e]" accesskey="e"><span>View source</span></a></li>
					<li id="ca-history" class="collapsible "><a href="https://developer.ridgerun.com/wiki/index.php?title=Gpio-int-test.c&amp;action=history" title="Past revisions of this page [alt-h]" accesskey="h"><span>View history</span></a></li>
			</ul>
</div>

<!-- /0 -->

<!-- 1 -->
<div id="p-cactions" class="vectorMenu emptyPortlet">
	<h5><span>Actions</span><a href="#"></a></h5>
	<div class="menu">
		<ul>
					</ul>
	</div>
</div>

<!-- /1 -->

<!-- 2 -->
<div id="p-search">
	<h5><label for="searchInput">Search</label></h5>
	<form action="/wiki/index.php" id="searchform">
		<input name="title" value="Special:Search" type="hidden">
				<input id="searchInput" name="search" title="Search RidgeRun Developer Connection [alt-f]" accesskey="f" type="text">
		<input name="go" class="searchButton" id="searchGoButton" value="Go" title="Go to a page with this exact name if exists" type="submit">
		<input name="fulltext" class="searchButton" id="mw-searchButton" value="Search" title="Search the pages for this text" type="submit">
			</form>
</div>

<!-- /2 -->
			</div>
		</div>
		<!-- /header -->
		<!-- panel -->
			<div id="panel" class="noprint">
				<!-- logo -->
					<div id="p-logo"><a style="background-image: url(/wiki/skins/common/images/logorr.png);" href="https://developer.ridgerun.com/wiki/index.php/Main_Page" title="Visit the main page"></a></div>
				<!-- /logo -->
				
<!-- navigation -->
<div class="portal" id="p-navigation">
	<h5>Navigation</h5>
	<div class="body">
				<ul>
					<li id="n-mainpage"><a href="https://developer.ridgerun.com/wiki/index.php/Main_Page" title="Visit the main page [alt-z]" accesskey="z">Main Page</a></li>
					<li id="n-Recent-changes"><a href="https://developer.ridgerun.com/wiki/index.php/Special:RecentChanges">Recent changes</a></li>
				</ul>
			</div>
</div>

<!-- /navigation -->

<!-- Useful Links -->
<div class="portal" id="p-Useful_Links">
	<h5>Useful Links</h5>
	<div class="body">
				<ul>
					<li id="n-RidgeRun-Blog"><a href="https://www.ridgerun.com/www/index.php/blog.html">RidgeRun Blog</a></li>
					<li id="n-Download-Center"><a href="https://www.ridgerun.com/www/index.php/download-center.html">Download Center</a></li>
					<li id="n-TI-E2E-Community"><a href="http://e2e.ti.com/">TI E2E Community</a></li>
					<li id="n-TI.27s-Developers-Wiki"><a href="http://wiki.davincidsp.com/">TI's Developers Wiki</a></li>
				</ul>
			</div>
</div>

<!-- /Useful Links -->

<!-- SEARCH -->

<!-- /SEARCH -->

<!-- TOOLBOX -->
<div class="portal" id="p-tb">
	<h5>Toolbox</h5>
	<div class="body">
		<ul>
					<li id="t-whatlinkshere"><a href="https://developer.ridgerun.com/wiki/index.php/Special:WhatLinksHere/Gpio-int-test.c" title="List of all wiki pages that link here [alt-j]" accesskey="j">What links here</a></li>
						<li id="t-recentchangeslinked"><a href="https://developer.ridgerun.com/wiki/index.php/Special:RecentChangesLinked/Gpio-int-test.c" title="Recent changes in pages linked from this page [alt-k]" accesskey="k">Related changes</a></li>
																																										<li id="t-specialpages"><a href="https://developer.ridgerun.com/wiki/index.php/Special:SpecialPages" title="List of all special pages [alt-q]" accesskey="q">Special pages</a></li>
									<li id="t-print"><a href="https://developer.ridgerun.com/wiki/index.php?title=Gpio-int-test.c&amp;printable=yes" rel="alternate" title="Printable version of this page [alt-p]" accesskey="p">Printable version</a></li>
						<li id="t-permalink"><a href="https://developer.ridgerun.com/wiki/index.php?title=Gpio-int-test.c&amp;oldid=2604" title="Permanent link to this revision of the page">Permanent link</a></li>
						</ul>
	</div>
</div>

<!-- /TOOLBOX -->

<!-- LANGUAGES -->

<!-- /LANGUAGES -->
			</div>
		<!-- /panel -->
		<!-- footer -->
		<div id="footer">
											<ul id="footer-info">
																	<li id="footer-info-lastmod"> This page was last modified on 10 August 2011, at 13:44.</li>
																							<li id="footer-info-viewcount">This page has been accessed 37,660 times.</li>
															</ul>
															<ul id="footer-places">
																	<li id="footer-places-privacy"><a href="https://developer.ridgerun.com/wiki/index.php/RidgeRun_Developer_Connection:Privacy_policy" title="RidgeRun Developer Connection:Privacy policy">Privacy policy</a></li>
																							<li id="footer-places-about"><a href="https://developer.ridgerun.com/wiki/index.php/RidgeRun_Developer_Connection:About" title="RidgeRun Developer Connection:About">About RidgeRun Developer Connection</a></li>
																							<li id="footer-places-disclaimer"><a href="https://developer.ridgerun.com/wiki/index.php/RidgeRun_Developer_Connection:General_disclaimer" title="RidgeRun Developer Connection:General disclaimer">Disclaimers</a></li>
															</ul>
										<ul id="footer-icons" class="noprint">
								<li id="footer-icon-poweredby"><a href="http://www.mediawiki.org/"><img src="Gpio-int-test_files/poweredby_mediawiki_88x31.png" alt="Powered by MediaWiki" height="31" width="88"></a></li>
											</ul>
			<div style="clear:both"></div>
		</div>
		<!-- /footer -->
		<!-- fixalpha -->
		<script type="text/javascript"> if ( window.isMSIE55 ) fixalpha(); </script>
		<!-- /fixalpha -->
		
<script>if (window.runOnloadHook) runOnloadHook();</script>
<script type="text/javascript">
var gaJsHost = (("https:" == document.location.protocol) ? "https://ssl." : "http://www.");
document.write(unescape("%3Cscript src='" + gaJsHost + "google-analytics.com/ga.js' type='text/javascript'%3E%3C/script%3E"));
</script><script src="Gpio-int-test_files/ga.js" type="text/javascript"></script>
<script type="text/javascript">
var pageTracker = _gat._getTracker("UA-2001544-1");
pageTracker._trackPageview();
</script>		<!-- Served in 0.224 secs. -->			

</body></html>