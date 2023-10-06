---
sort: 3
---

# Custom Icon Loader


Starting with `v3.1.3 - revision 0` HDLBinst will be capable of loading custom icons (wich will be the icon that the game uses as save file)


If you want to contribute to the icon database you must:

1. Find the game icom (from the save file is the best option)
2. check if the icon file size is smaller than 200kb
3. check all the game variants ELF ID
4. send me the file and a list with the ELF ID of the game variants (search the game title on this Database to see how many variants are available and copy the ELF of each

Example:

_GTA San andreas_

Provide icon file (example name: GTA_SAR.ico)

and a list of the ELF ID's like this one

```ini
SCES_515.41=GTA_SAR.ico
SCES_525.41=GTA_SAR.ico
SCES_529.27=GTA_SAR.ico
SLES_515.41=GTA_SAR.ico
SLES_525.41=GTA_SAR.ico
SLPM_552.92=GTA_SAR.ico
SLES_529.27=GTA_SAR.ico
SLPM_659.84=GTA_SAR.ico
SLPM_667.88=GTA_SAR.ico
SLUS_209.46=GTA_SAR.ico
```