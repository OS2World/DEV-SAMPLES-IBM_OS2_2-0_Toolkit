.*--------------------------------------------------------------------
.* This file contains the tagged source for IPF Sample
.*--------------------------------------------------------------------

:userdoc.

.*--------------------------------------------------------------------
.* Provide a title for the title line of the main window
.*--------------------------------------------------------------------

:title.Information Presentation Facility Sample

.*--------------------------------------------------------------------
.* Allow only heading level 1 to appear in the contents window and
.* specify no control area for pushbuttons
.*--------------------------------------------------------------------

:docprof toc=1 ctrlarea=none.

.*--------------------------------------------------------------------
.* Identify the heading level entries to be displayed in the contents
.* window (Personal System/2)
.*--------------------------------------------------------------------

:h1 id=content1 x=left y=top width=100% height=100% scroll=none
    clear.Personal System/2

.*--------------------------------------------------------------------
.* Identify and display a bitmap (Office)
.*--------------------------------------------------------------------
.*--------------------------------------------------------------------
.* Specify a segmented hypergraphic area to link split screen support
.*--------------------------------------------------------------------

:artwork name='OFFICE.bmp' align=center.
:artlink.
:link reftype=hd res=01 x=350 y=100 cx=190 cy=120 dependent.
:eartlink.

.*--------------------------------------------------------------------
.* Specify an automatic link to a child window (Continue)
.*--------------------------------------------------------------------

:link reftype=hd refid=note1 vpx=left vpy=top vpcx=55% vpcy=10%
      scroll=none rules=border titlebar=none auto child.

.*--------------------------------------------------------------------
.* Display an IC window using a note tag (Continue)
.*--------------------------------------------------------------------

:h1 id=note1 hide.Continue
:note.Double click on the PS/2 to continue...

.*--------------------------------------------------------------------
.* Display a composite window with a parent window panel containing
.* multiple windows (Composite)
.*--------------------------------------------------------------------

:h1 res=01 x=10% y=20% width=80% height=60%
    titlebar=none rules=none scroll=none hide viewport.Composite

.*--------------------------------------------------------------------
.* Specify an automatic link to a child window (486 Technology)
.*--------------------------------------------------------------------

:link reftype=hd refid=view1 vpx=left vpy=top vpcx=50% vpcy=100%
      rules=border scroll=vertical auto child.

.*--------------------------------------------------------------------
.* Specify an automatic link to a child window (Model 90)
.*--------------------------------------------------------------------

:link reftype=hd refid=view2 vpx=right vpy=top vpcx=50% vpcy=100%
      titlebar=none rules=border scroll=none auto child.

.*--------------------------------------------------------------------
.* Display a window with scrollable text (486 Technology)
.*--------------------------------------------------------------------

:h1 id=view1 hide.486 Technology

.*--------------------------------------------------------------------
.* Place a bitmap above the lines of text for a graphics heading
.* (Heading)
.*--------------------------------------------------------------------

:artwork name='heading.bmp' runin.

:p.Make your move to 486 power, and go as fast as you like with the
.*
.*--------------------------------------------------------------------
.* Specify a hypertext link to a secondary window (Trademarks)
.*--------------------------------------------------------------------
.*
:link reftype=hd refid=view3 dependent group=2.IBM:elink.
.*
Model 90 XP 486 series from
.*
.*--------------------------------------------------------------------
.* Specify a hypertext link to a secondary window (Personal System/2)
.*--------------------------------------------------------------------
.*
:link reftype=hd refid=view4 dependent group=2.Personal System/2.:elink.
.*
Built around the latest Intel486 SX and DX
.*
.*--------------------------------------------------------------------
.* Specify a hypertext link to a secondary window (Microprocessor)
.*--------------------------------------------------------------------
.*
:link reftype=hd refid=view5 dependent group=2.microprocessor:elink.
.*
technology, the PS/2s in this series offer a range of speed, memory
and storage capacity to suit your needs and your budget. And because
all Model 90 XP 486s are designed for easy upgrading and expansion,
you get a solution that's suited not only for today but for tomorrow.
.*
:p.Whether you select a 20 MHz, 25 MHz or 33 MHz system, you benefit
from balanced Micro Channel based performance. That means you get the
most from the 90 XP 486's
.*
.*--------------------------------------------------------------------
.* Specify a hypertext link to a secondary window (Resoures)
.*--------------------------------------------------------------------
.*
:link reftype=hd refid=view6 dependent group=2.resources:elink.
.*
from processor to
.*
.*--------------------------------------------------------------------
.* Specify a hypertext link to a secondary window (Mouse)
.*--------------------------------------------------------------------
.*
:link reftype=hd refid=view7 dependent group=2.ports:elink.
.*
to XGA graphics to SCSI fixed disks to optimized memory. So you
realize the the full potential of
.*
.*--------------------------------------------------------------------
.* Specify a hypertext link to a secondary window (486 Power)
.*--------------------------------------------------------------------
.*
:link reftype=hd refid=view8 dependent group=2.486 power:elink.
.*
through the advanced technology of PS/2.

.*--------------------------------------------------------------------
.* Display an IC window with a graphic illustration (Model 90)
.*--------------------------------------------------------------------

:h1 id=view2 hide.Model 90
:artwork name='model90.bmp' align=center.

.*--------------------------------------------------------------------
.* Display an IC window using color and simple list tags (Trademarks)
.*--------------------------------------------------------------------

:h1 id=view3 x=56 y=1 width=47 height=4 scroll=vertical
    hide.Trademarks
:sl compact.
:color fc=yellow bc=blue.
:li.IBM, Personal System/2, PS/2, OS/2,
:li.and Micro Channel are registered
:li.trademarks of International
:li.Business Machines Corporation.
:li.
:li.UNIX is a registered trademark
:li.of UNIX System Laboratories, Inc.
:li.
:li.486, Intel486, i486,and 386 are
:li.trademarks of Intel Corporation.
:esl.

.*--------------------------------------------------------------------
.* Display an IC window using various highlighted phrase tags
.* (Personal System/2)
.*--------------------------------------------------------------------

:h1 id=view4 x=left y=top width=100% height=100% scroll=vertical
    hide.Personal System/2

:hp2.Why PS/2?:ehp2.
:p.
Here are some of the reasons why PS/2 stands out as the best solution
for your business needs.
:p.
:hp3.Technological leadership :ehp3.through Micro Channel architecture,
integrated construction and advanced design (by combining Very Large
Scale Integration and Surface Mount Technology), and SCSI support for
large data storage.
:p.
:hp3.Extensive communications capabilities :ehp3.through a wide range
of connectivity options, provide concurrent support for intelligent
communications adapters and coprocessors, thanks to Micro Channel
architecture.
:p.
:hp3.Compatibility and expandability :ehp3.to protect your investment
since the PS/2s you have today work with existing products and
programs, and with those you'll need tomorrow.
:p.
:hp3.Service and support :ehp3.that provide you with everything from
fast parts delivery to onsite services to system planning to 24-hour
phone support, all at a competitive price.
:p.
:hp3.Business Partners :ehp3.who enhance PS/2 capabilities by helping
customers choose, customize and configure hardware and software to
meet a range of needs.
:p.
:hp3.Quality and reliability :ehp3.that ensure PS/2s are built to
perform smoothly and dependably year after year.

.*--------------------------------------------------------------------
.* Display an IC window using artwork tags (Microprocessor)
.*--------------------------------------------------------------------

:h1 id=view5 x=left y=top width=100% height=100% scroll=vertical
    hide.486 Microprocessor
:p.A closer look at i486 processing complexes:
:p.
:hp2.i486 SX, 20 MHz:ehp2.
:p.
 Entry level 486 processor providing the equivalent of 386 33 MHz
performance
:p.
 High power processing, affordably priced
:p.
 Integrated 8KB memory cache for "no-wait" processing
:p.
 20 MHz 80487 SX coprocessor upgrade for extra fast completion of
numeric intensive tasks
:p.
 Easy upgrade to 25 MHz or 33 MHz to keep pace with changing needs

:p.
:artwork name='micro20.bmp' runin.

:p.
:hp2.i486 DX, 25 MHz:ehp2.
:p.
 High speed 486 processor with full complement of integrated
components
:p.
 On-chip floating point unit for extra calculating speed
:p.
 Integrated 8KB memory cache for "no-wait" processing
:p.
 On-board interface for optional 256KB L2 cache
:p.
 Easy upgrade to 33 MHz when you want to work even faster

:p.
:artwork name='micro25.bmp' runin.

:p.
:hp2.i486 DX, 33 MHz:ehp2.
:p.
 The fastest 486 processor available today for applications where
every nanosecond counts
:p.
 Full complement of integrated components, including 8 KB memory
cache and floating point unit for maximum performance and speed
:p.
 On-board interface for optional 256KB L2 cache
:p.
 Upgradability to future technology, higher speed processors are soon
to come

:p.
:artwork name='micro33.bmp' runin.

.*--------------------------------------------------------------------
.* Display an IC window using parameter list tags (Resources)
.*--------------------------------------------------------------------

:h1 id=view6 x=left y=top width=100% height=100% scroll=vertical
    hide.Resources
:p.Feature                      Benefit
   컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
:p.
:hp7.Advanced i486 SX and DX processor complexes:ehp7.
:parml compact tsize=30 break=none.
:pt.
:pd. Offer flexibility in choosing the right performance for the
right price
:pt.
:pd. Include 8KB memory cache, DX complexes also come with an
integrated floating point unit and can support an optional 256KB cache
:pt.
:pd. Handle numeric intensive business and technical tasks at top
speeds
:pt.
:pd. Protect your investment by allowing future upgrades from 20 MHz
to 25 MHz to 33 MHz and, in time, beyond
:eparml.

:p.
:hp7.Built-in XGA graphics:ehp7.
:parml compact tsize=30 break=none.
:pt.
:pd. Deliver faster performance for existing VGA applications and
support more colors, too
:pt.
:pd. Supply 1,024 x 768 addressability, with no need for separate
adapter
:pt.
:pd. Support today's windowing environments with enhanced hardware
assist features
:eparml.

:p.
:hp7.Enhanced memory design:ehp7.
:parml compact tsize=30 break=none.
:pt.
:pd. Includes caching functions that make frequently used information
available to the processor with zero wait states
:pt.
:pd. Optimizes to 486 processing power with interleaved memory access
techniques
:pt.
:pd. Performs parity checking for improved reliability and data
integrity
:pt.
:pd. Adjusts automatically to allow memory SIMM pairs of different
speeds to be supported
:eparml.

:p.
:hp7.SCSI Adapter with Cache:ehp7.
:parml compact tsize=30 break=none.
:pt.
:pd. Enables attachment of up to seven SCSI devices, including high
performance fixed disks, without using another expansion slot
:pt.
:pd. Works with Micro Channel to enhance overall system performance
:eparml.

:p.
:hp7.4MB or 8MB memory, expandable to 32MB on planar:ehp7.
:parml compact tsize=30 break=none.
:pt.
:pd. Makes the Model 90 XP 486 series ideal for OS/2 and UNIX based
operating environments
:pt.
:pd. Saves expansion slots by building on the system board
:eparml.

:p.
:hp7.Micro Channel:ehp7.
:parml compact tsize=30 break=none.
:pt.
:pd. Provides efficient data paths for fast, reliable, balanced
performance
:pt.
:pd. Supports multiple tasks and concurrent I/O operations
:pt.
:pd. Protects investment by providing a platform for future expansion
and growth
:eparml.

:p.
:hp7.Four storage bays (two available):ehp7.
:parml compact tsize=30 break=none.
:pt.
:pd. Allow flexibility in configuring data storage
:pt.
:pd. Enable installation of a 5.25 inch diskette drive for easy data
transfer to and from different diskette sizes
:pt.
:pd. Make room for up to three fixed disk drives providing total
storage up to 1.12GB
:eparml.

:p.
:hp7.Initial Machine Load (IML):ehp7.
:parml compact tsize=30 break=none.
:pt.
:pd. Provides system reference and setup instructions on fixed disk,
eliminating the need for separate diskettes
:pt.
:pd. Simplifies implementation of future system program upgrades
:eparml.

:p.
:hp7.Selectable boot:ehp7.
:parml compact tsize=30 break=none.
:pt.
:pd. Lets you "boot" from any diskette or disk drive so you can use
different operating systems
:eparml.

:p.
:artwork name='inside90.bmp' runin.

.*--------------------------------------------------------------------
.* Display an AC window for animation using the acviewport tag
.* (Mouse Port)
.*--------------------------------------------------------------------

:h1 id=view7 x=right y=top width=30% height=70% scroll=none
    group=4 hide.Mouse Port
:acviewport dll='IPF' objectname='IPFMain' objectid=1.

.*--------------------------------------------------------------------
.* Display an IC window using ordered list tags (486 Power)
.*--------------------------------------------------------------------

:h1 id=view8 x=left y=top width=100% height=100% scroll=none
    hide.486 Power
:p.Here are some of the ways you can put the Model 90 XP 486 series to
work for you:
:ol.
:li.Do financial analyses, modeling, complex spreadsheets and other
numeric intensive applications at your choice of 20 MHz, 25MHz or
33 MHz processing speed
:li.Run power hungry, high resolution imaging and graphics programs
for science and engineering, i486 DX processor models excel at CAD/CAM
:li.Meet desktop publishing demands and deadlines more easily and
efficiently than ever
:li.Create presentation graphics with a professional appearance
:li.Increase the productivity of your programming staff with quick
turn around on compiles and tests
:eol.

:euserdoc.
x
