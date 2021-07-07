# why HDL Batch Installer is superior to other programs?

i´ll list it´s strengths compared to other programs:

<!--
__HDL Dump Helper GUI__ | __HDL Batch Installer__ |
------------------- | -------------------- |
Uses __older hdldump__ | uses __latest hdldump__ _(automatically updated during release creation)_ |
__needs Java 32bits__ | it's written on C++, so __no dependencies are needed__ |
Installs games __1 by 1__ | capable of selecting __multiple Games__, from different paths before installing |
HDD must be connected before launching the program | Capable of scanning new HDDs __without restarting program__ |
User must enter game title __manually for every game__ | __Original game title automatically assigned__ from internal database |
__Can't hide games__ from HDD-OSD/PS2BBN | __Capable of hiding games__ from HDD-OSD/PS2BBN |
-->
<table style="width:100%">
  <tr>
    <th>winhiip</th>
    <th>HDLBInst</th>
  </tr>
  <tr>
    <td style="color:Tomato;">Limited to <b>255 games</b></td>
    <td>Limited to uLaunchELF partition limit (according to source code: ~1400 games)</td>
  </tr>
  <tr>
    <td>Can´t read 1tb/2tb HDDs</td>
    <td>Up to 2tb HDDs are supported</td>
  </tr>
  <tr>
    <td><b>Abandoned</b> project </td>
    <td>Project on <b>active development</b> (Even if this GUI Get´s abandoned, you can update HDLDump</td>
  </tr>
  <tr>
    <td>Only supports DVD5 ISO´s </td>
    <td>Supports DVD5/DVD9 ISO´s, BIN Images, Nero Images, .iml files and global images</td>
  </tr>
  <tr>
    <td>Games without Support for HDD-OSD or PS2BBN</td>
    <td>Games are compatible with HDD-OSD and PS2BBN (if miniOPL Is provided, aka: <code>boot.kelf</code>)</td>
  </tr>
  <tr>
    <td>issues when handling HDDs formatted by uLaunchELF </td>
    <td>Compatible with uLaunchELF HDD´s (uLe 4.43a 41e4ebe or <a href="https://github.com/israpps/wLaunchELF_ISR">4.43x_isr</a> are recomended)</td>
  </tr>
  <tr>
    <td>Randomly corrupts HDD (or it's MBR program)</td>
    <td> </td>
  </tr>
  <tr>
    <td>Filename used as game title</td>
    <td> original game title <b>automatically assigned</b> from internal database</td>
  </tr>
  <tr>
    <td><b>Can't hide</b> games from HDD-OSD/PS2BBN </td>
    <td>Capable of hiding games from HDD-OSD/PS2BBN</td>
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
