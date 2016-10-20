ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»
º                                                                        º
º  Arcadia Workplace Companion                                           º
º  Version 1.53 Release Notes: April 22, 1993                            º
º                     Updated: December 8, 1993                          º
º  Copyright (C) 1993 Arcadia Technologies, Inc.                         º
º                                                                        º
ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼


ÄÄÄÄÄÄÄÄÄÄÒÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
Contents: º
ÍÍÍÍÍÍÍÍÍÍ¼

0. Demo Notes
1. Release Notes
2. Link Names (not available for the demo version)
3. Performance Tips
4. Modem Dialer
5. Setting Your Local City

<<<=========================  Demo Notes  ============================>>>
<<<                                                                   >>>
<<<   Please note that this version of demo program will expire       >>>
<<<   on August 31, 1994.  It is likely a new version of the demo     >>>
<<<   is available before that date.  Please check your BBS for       >>>
<<<   up-to-date information of the demo program.                     >>>
<<<                                                                   >>>
<<<   Please also note that the production version of the program     >>>
<<<   will be at a higher version. As of December 8, 1993, 1.55 is    >>>
<<<   the version shipped by Arcadia Technologies,Inc.                >>>
<<<                                                                   >>>
<<<   The demo program does not allow to import/export files and      >>>
<<<   to print various reports.                                       >>>
<<<                                                                   >>>
<<<   To unzip ARCADIA.ZIP properly, please read the UNZIP.TXT file.  >>>
<<<                                                                   >>>
<<<   To order:  Please read the ORDER.TXT file.                      >>>
<<<                                                                   >>>   
<<<   Please note that both UNZIP.TXT and ORDER.TXT files will not    >>>
<<<   be copied by the installation program (INST_WPC.EXE).           >>>
<<<                                                                   >>>
<<<===================================================================>>>


ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÒÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
1. Release Notes: º
ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼

Thank you for purchasing the Arcadia Workplace Companion, the finest OS/2 
integrated personal information manager available!  

This is the production version of the Arcadia Workplace Companion. We have 
received many suggestions from end users and have incorporated many of them 
into our design. However, we are constantly striving to improve the 
Companion's performance in all areas, and will continue to enhance its 
effectiveness as an indispensable productivity tool. Please let us know how 
you feel about the software. We can be reached through the address and phone 
numbers listed in the manual. Your support to the Companion is important 
to us and the OS/2 community.

NOTE:  Please be sure to return your registration materials to receive an 
       additional 90 days of free technical support.

ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÒÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
2. Link Names: º
ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼

The Arcadia Workplace Companion allows you to import information that is
stored in other PIM Products. The Import facility supports ASCII (CSV)
file formats to import data.

The Import/Export facility is very easy to use. You simply need to
establish links between the fields you are bringing in and the
corresponding fields in the Companion. To facilitate this process,
you may save the links that you create so that they can be reused.

For your convenience, Arcadia has shipped several pre-made link names
for some of the more popular Windows PIM products. Selecting one of these
Link Names in the import utility fills the Link List with all of the
links that were created.

In order to successfully use these Link Names, there are several issues
that you need to take into consideration. The Windows products that have
link names are listed below:

  1. Lotus Organizer Version 1.0
  2. Polaris PackRat Version 4.0
  3. YourWay Version 2.2 (Prisma)

As we release additional versions of the software this list will continue
to grow. Information on how to use each of these Link Name with their
associated products is shown below:

Importing from Lotus Organizer:
ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ

Lotus stores its address information in one long string. In order to
successfully import this data into your Companion, you need to break up
the address into multiple lines. For example:

  Old Information:                      New Information:
  ----------------                      ----------------

  735 West Duarte Road, Suite 207       735 West Duarte Road
  Arcadia, CA                           Suite 207
                                        Arcadia
                                        CA

When you import the address it is linked to four different Companion
fields: 1)Address1, 2)Address2, 3)City, and 4)State. This operation works
correctly only if each piece of information is on its own line. Thus,
even if you do not have a second address line (i.e. Suite 207), you
still need to add a blank line to ensure that the City and State are
imported correctly.

The two Lotus User fields are imported to the first two User fields in
the Companion: User 1 and User 2. The Type field is linked to the third
User field: User 3.

The Extn. field for the phone number is appended to the end of the Phone
Number in the Companion. Unfortunately, if you would like to break this
number up, you have to do it by hand.

When you export the data from Lotus Organizer, simply use the Link All
button to export the data in the order that it is listed.


Importing from Polaris PackRat:
ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ

Like the Companion, PackRat stores a lot of data for each person.
Additionally, the data is stored in much the same way as the Companion.

When you export your data from PackRat, take note of the following
considerations:

  1. Make sure that you use a comma (,) as the separator character.

  2. Do not Include Phone Number Labels for the phone numbers.

  3. Do not Include Notes. The way in which PackRat exports notes is
     not true ASCII (CSV) format. There is no way to successfully import
     notes for entries stored in PackRat.

  4. Export all of the fields from PackRat in the same order that they
     appear in the list (alphabetically). Even though not all of the
     information will make it into the Companion, all of the fields need
     to be exported for the Polaris PackRat Link Name to function
     properly.

The following PackRat fields are not imported into the Companion:

 - Client Rate                         - E-Mail Name
 - Date                                - Full Name
 - Primary Department                  - Nickname
 - Secondary Department                - Resource Rate
 - E-Mail Destination

If some of these fields are very important to you, you may import them
into one of the five custom fields. By default the four Key fields and
the Assistant fields are imported in the Companion User fields. You may
modify these links according to your needs.

It is assumed that the phone numbers you have stored are in the following
order:

 1. Business Number
 2. Fax Number
 3. Home Number
 4. Custom Phone Number

If this is not the way you ordered your phone numbers in PackRat, you may
modify the Link Name to suit your needs. Additionally, the entire phone
number, including the country code, area code, phone number, and extension
are all stored in the Phone Number field in the Companion. Unfortunately, if
you would like to break up these values, you will have to do it by hand.


Importing from Prisma YourWay:
ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ

YourWay store very limited information for each person in its card file.
All of the information stored in YourWay can be successfully imported into
the Companion.

When you export the data, take note of the following considerations:

  1. Make sure that you select the CSV format when you export the data

  2. Use the Select All button to export all of the fields in the same
     order that they are shown in the list.

The Greeting is linked to the first Companion User field. The Investment
field is linked to the second Companion User field.

ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÒÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
3. Performance Tips: º
ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼


As you use the various modules and the size of your databases grows, you may
experience some performance degradation, specifically in the use of the 
Telephone/Address Book. A list of useful tips has been compiled to help
maximize your productivity.

  1.  Minimize the main Clock/Calendar window rather than closing it if you
      frequently use it or any of the Companion's modules.

  2.  Minimize frequently used Companion modules rather than opening and 
      closing them with each usage.

  3.  When using the Telephone/Address Book module, use a filter when working 
      with a specific subset of its contents.  This will cut down on the 
      number of unnecessary entries loaded into module. This can be 
      especially helpful if your database exceeds 500 records.

  4.  OS/2 performance in general can be greatly affected by a lack of free
      hard drive space. Maintaining 12-20 megabytes of free space can 
      improve the performance of your system.



ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÒÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
4. Modem Dialer: º
ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼

The Arcadia Dialer, found in the Phone Book, requires you to 
incorporate the proper initialization string, found on the first 
Phone page of the Preferences Notebook, so that your modem will 
know what to do.  The default initialization string in Arcadia is 
"ATQ0V0E1M1L2".  This is read by the modem as "AT", "Q0", "V0", 
"E1", "M1" and "L2".  These are six separate commands and "0" is 
the numeral zero.  The following is a breakdown of each commands' 
respective function for your modem.  

Note:  When entering modem commands, be sure to use capital letters. 

 "AT" - 
This command is required by the modem.  
"AT" calls your modem to attention.  This is the standard command 
required at the beginning of every modem initialization string.  


 "Q0" - 
This command is required by Arcadia.  
"Q" commands relate to the modem's ability to display Result Codes.  
"Q0" means that this function is enabled.  


 "V0" - 
This command is required by Arcadia.  
"V" commands relate to whether the Result Code is Numerical (terse) 
or Verbal (verbose).  "V0" defines Numerical Result Codes.  


 "E1" - 
This command is required by Arcadia.  
"E" commands deal with your modem's ability to display Command Local 
Echo.  "E1" means that the Command Local Echo function is enabled.  


 "M1" - 
This command is required by Arcadia.  
"M" commands control your modem's speaker.  "M1" usually means that 
your modem's speaker is enabled.  This function allows you monitor the 
other party's handset so that you know when to pick up your handset.  
As a standard procedure for most modems, Arcadia recommends that you 
pick up the handset right after the other party picks up his/hers.  Your 
modem's speaker will let you monitor when the other party has done so.  


 "L2" - 
This command is optional.  
On some brands of modems the "L" command is used to control the modem 
speaker volume.  On others, the "M" command may control volume.  If you 
feel that your modem speaker is too loud or too quiet, consult your 
modem's manual to change the volume.  You may delete the "L2" from the 
Arcadia initialization string if your modem does not support the "L" 
command.  This will allow you to use the modem's default volume setting.  

On some modems, different characters are assigned to the same function.  
If you have problems with dialing out, check in your modem's manual to 
see whether the Arcadia initialization string commands are compatible 
with your modem.  If they are not, make the necessary changes in the 
Preferences Notebook.  

NOTE:  Using the "ATZ" to replace the initialization string is not 
recommended by Arcadia.  This command will give you all of the default 
modem settings, which are probably incompatible with Arcadia's needs.  
However, if you have a lot of trouble with your modem in finding the 
correct initialization string, try deleting the entire Arcadia 
initialization string from the Preferences Notebook.  This sometimes works 
when all else fails.  



ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÒÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
5. Setting Your Local City: º
ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼

In order for your Companion to determine the correct local time from other 
time zones, you must set your city as the Local City.  To set the Local City, 
do the following:  

1.  Bring up the Companion from the OS/2 desktop icon view

2.  RMB (Right-Mouse-Button) click over the Clock/Calendar area to bring 
    up the Clock/Calendar context menu

3.  Select the Options/Local city... choice to bring up the Local City 
    dialog

4.  Use the drop-down list to select your city; if your city is not on 
    the list, choose any city that is in the same time zone as your city.  
    Preferably, choose the closest city in the same state, province, 
    country, etc.  

5.  Click on the Ok button to save your selection.  <<  Very Important!!  >>

