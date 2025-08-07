# Keychron K2 (V2) config files

Please note that this is for the Keychron K2 (version 2) only! Version 2 (in contrast to version 1) is by default angled and the feets have 2 different positions.

I have only changed the `ansi` layout and `via` keymap, the others remain the same/default config. If you have a different layout or do not need via, please adjust not only the files but also commands below accordingly.

## Environment setup

```
# Step 1: downloading git repos
git clone https://github.com/Robin-Sch/keychron-k2
git clone https://github.com/SonixQMK/qmk_firmware.git
git clone https://github.com/SonixQMK/SonixFlasherC

# Step 2: downloading git submodules (for qmk firmware)
cd qmk_firmware
make git-submodule
cd ..

# Step 3: installing qmk
python3 -m pip install --user qmk # or sudo pacman -S qmk
qmk setup -H qmk_firmware

# Step 4: installing SonixFlasherC
cd SonixFlasherC
make sonixflasher
cd ..

# Step 5: put keychron k2 config in qmk_firmware
ln -s keychron-k2 qmk_firmware/keyboards/keychron/k2/rgb/v2
```

## Compiling

Every time you change the config files, you need to re-compile and re-flash the keyboard.

```
qmk compile -kb keychron/k2/rgb/v2/ansi -km via
```

## Flashing

```
sudo SonixFlasherC/sonixflasher --vidpid 0c45/7040 --file qmk_firmware/keychron_k2_rgb_v2_ansi_via.bin
```

Then press Fn + Esc to enter the bootloader (or use tweezers under spacebar)

## Sources
- [Docs](https://docs.qmk.fm)
- [Ansi via keymap](https://github.com/SonixQMK/qmk_userspace_via/blob/main/keyboards/keychron/k2/rgb/v2/ansi/keymaps/via)
- - Note that it's basically the same as the [default config](https://github.com/SonixQMK/qmk_firmware/tree/sn32_develop/keyboards/keychron/k2/rgb/v2/ansi/keymaps/default)
