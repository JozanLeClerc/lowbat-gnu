# README in progress

# lowbat

Very small script that runs in the background and warns you when your battery is low until you plug your laptop in. It is POSIX compliant, which is nice.

## Dependencies

+ `libnotify`
+ `espeak`

## Installation

Open a terminal and run these commands:

```shell
git clone https://github.com/JozanLeClerc/lowbat.git
cd lowbat
sudo make install
```

Next you must find a way to get the script running when loging in. Add this to your startup programs manager of choice:

```shell
lowbat > /dev/null 2>&1 &
```

## Uninstallation

```shell
sudo make uninstall
```
