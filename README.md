# Custom Bootloader

Custom Bootloader to update firmware through UART, developed on the FRDM-KL46Z board using Kinetis Design Studio IDE.

## Built With

* [Kinetis Design Studio IDE](https://www.nxp.com/design/design-center/development-boards-and-designs/design-studio-integrated-development-environment-ide:KDS_IDE) - The IDE used.
* [FRDM-KL46Z](https://www.nxp.com/design/design-center/development-boards-and-designs/general-purpose-mcus/freedom-development-platform-for-kinetis-kl3x-and-kl4x-mcus:FRDM-KL46Z) - The Kit used.

## Versioning

Ver 0.0

## Authors

* **Nguyen The Anh** - [AnhNT2920](https://github.com/AnhNT2920)

## License

This project is public for use.

## Important notes

* This bootloader works on the MKL46Z series.
* The UART baud rate is 115200.
* Can work with 3 types of address (16-bit, 24-bit, 32-bit) record in Srec file.
* Boot mode should be run initially for stable operation.
* Maximum Flash size that can be written for the new update is 214 kB.
* To enter Boot mode in the first run, hold the Boot button (switch 2) then press reset.
