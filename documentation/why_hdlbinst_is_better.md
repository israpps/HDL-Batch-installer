---
sort: 1
---

# why HDL Batch Installer is superior to other programs?

i´ll list it´s strengths compared to other programs:

<!--
-->
<table style="width:100%">
  <tr>
    <th>winhiip</th>
    <th>HDLBInst</th>
	<th>HDL Dump helper GUI</th>
	<th>HDLBATCH</th>
  </tr>
  <tr>
    <td style="color:Tomato;">Limited to <b>255 games</b></td>
    <td style="color:MediumSeaGreen;">Limited to uLaunchELF partition limit (Acording to <a href="https://github.com/israpps/wLaunchELF_ISR/blob/e4e01be7a601e84ca2aa98a31cc2ef46017204f6/launchelf.h#L90">source code</a>: ~1400 games)</td> 
    <td style="color:MediumSeaGreen;">Limited to uLaunchELF partition limit (Acording to <a href="https://github.com/israpps/wLaunchELF_ISR/blob/e4e01be7a601e84ca2aa98a31cc2ef46017204f6/launchelf.h#L90">source code</a>: ~1400 games)</td>
    <td style="color:MediumSeaGreen;">Limited to uLaunchELF partition limit (Acording to <a href="https://github.com/israpps/wLaunchELF_ISR/blob/e4e01be7a601e84ca2aa98a31cc2ef46017204f6/launchelf.h#L90">source code</a>: ~1400 games)</td>
  </tr>  
  <tr>
    <td style="color:Tomato;">has it's own installation system (old)</td>
    <td style="color:MediumSeaGreen;">uses latest HDL-Dump</td>
    <td style="color:Tomato;">uses an older version of HDL-Dump</td>
    <td style="color:Tomato;">uses an older version of HDL-Dump</td>
  </tr>
  <tr>
    <td style="color:Tomato;">Can´t read 1tb and 2tb HDDs</td>
    <td style="color:MediumSeaGreen;">Up to 2tb HDDs are supported</td>
    <td style="color:MediumSeaGreen;">Up to 2tb HDDs are supported </td>
    <td style="color:MediumSeaGreen;">Up to 2tb HDDs are supported </td>
  </tr>
  <tr>
    <td style="color:Tomato;"><b>Abandoned</b> project </td>
    <td style="color:MediumSeaGreen;">Project on <b>active development</b> (Even if this GUI Get´s abandoned, you can update HDLDump)</td>
    <td style="color:Tomato;"><b>Abandoned</b> project </td>
    <td style="color:Tomato;"><b>Abandoned</b> project </td>
  </tr>
  <tr>
    <td style="color:MediumSeaGreen;">Capable of installing multiple games easily</td>
    <td style="color:MediumSeaGreen;">Capable of installing multiple games easily</td>
    <td style="color:Tomato;">User must select the games one by one</td>
    <td style="color:Tomato;">User must move the games into the batch file location (or the other way around)</td>
  </tr>
  <tr>
    <td style="color:MediumSeaGreen;">No dependencies</td>
    <td style="color:MediumSeaGreen;">No dependencies</td>
    <td style="color:Tomato;">Needs Java 32bits</td>
	<td style="color:MediumSeaGreen;">No dependencies</td>

  </tr>
  <tr>
    <td style="color:MediumSeaGreen;">Detects new HDDs without restart</td>
    <td style="color:MediumSeaGreen;">Detects new HDDs without restart</td>
    <td style="color:Tomato;">Must restart program to list new HDDs</td>
    <td style="color:Tomato;">Must restart Batch file to list new HDDs</td>
  </tr>
  <tr>
    <td style="color:Tomato;">Only supports DVD5 ISO´s </td>
    <td style="color:MediumSeaGreen;">Supports DVD5/DVD9 ISO´s, BIN Images, Nero Images, .iml files and global images</td>
	<td>Only supports DVD5/DVD9 ISO´s </td>
    <td style="color:MediumSeaGreen;">Supports DVD5/DVD9 ISO´s, BIN Images, Nero Images, .iml files and global images</td>
  </tr>
  <tr>
    <td style="color:Tomato;">Games without Support for HDD-OSD or PS2BBN</td>
    <td style="color:MediumSeaGreen;">Games are compatible with HDD-OSD and PS2BBN (if miniOPL Is provided, aka: <code>boot.kelf</code>)</td>
	<td style="color:Tomato;">Games without Support for HDD-OSD or PS2BBN</td>
	<td style="color:Tomato;">Games without Support for HDD-OSD or PS2BBN</td>
  </tr>
  <tr>
    <td style="color:Tomato;">issues when handling HDDs formatted by uLaunchELF </td>
    <td style="color:MediumSeaGreen;">Compatible with uLaunchELF HDD´s (uLe 4.43a 41e4ebe or <a href="https://github.com/israpps/wLaunchELF_ISR">4.43x_isr</a> are recomended)</td>
    <td style="color:MediumSeaGreen;">Compatible with uLaunchELF HDD´s </td>
    <td style="color:MediumSeaGreen;">Compatible with uLaunchELF HDD´s </td>
  </tr>
  <tr>
    <td style="color:Tomato;">Randomly corrupts HDD (or it's MBR program)</td>
    <td style="color:MediumSeaGreen;"> </td>
    <td style="color:Tomato;">game uninstall feature is unstable</td>
    <td></td>
  </tr>
  <tr>
    <td style="color:Tomato;">Filename used as game title</td>
    <td style="color:MediumSeaGreen;"> original game title <b>automatically assigned</b> from internal database</td>
	<td style="color:Tomato;">Filename used as game title</td>
    <td style="color:MediumSeaGreen;"> original game title <b>automatically assigned</b> from internal database</td>
  </tr>
  <tr>
    <td style="color:Tomato;"><b>Can't hide</b> games from HDD-OSD/PS2BBN </td>
    <td style="color:MediumSeaGreen;">Capable of hiding games from HDD-OSD/PS2BBN</td>
    <td style="color:Tomato;"><b>Can't hide</b> games from HDD-OSD/PS2BBN </td>
    <td style="color:Tomato;"><b>Can't hide</b> games from HDD-OSD/PS2BBN </td>
  </tr>
  <tr>
    <td style="color:MediumSeaGreen;">can format HDD into PS2 format</td>
    <td style="color:MediumSeaGreen;">can format HDD into PS2 format</td>
    <td style="color:Tomato;">Can't format HDD into PS2 format</td>
    <td style="color:Tomato;">Can't format HDD into PS2 format</td>
  </tr>
  <tr>
    <td style="color:Tomato;">can't browse partitions contents from windows explorer</td>
    <td style="color:MediumSeaGreen;">can browse partitions contents from windows explorer</td>
    <td style="color:Tomato;">can't browse partitions contents from windows explorer</td>
    <td style="color:Tomato;">can't browse partitions contents from windows explorer</td>
  </tr>
</table>
<!--
<table style="width:100%">
  <tr>
    <th>Firstname</th>
    <th>Lastname</th>
    <th>Age</th>
  </tr>
  <tr>
    <td>Jill</td>
    <td>Smith</td>
    <td>50</td>
  </tr>
  <tr>
    <td>Eve</td>
    <td>Jackson</td>
    <td>94</td>
  </tr>
</table>
-->


##### [Go back](./)
