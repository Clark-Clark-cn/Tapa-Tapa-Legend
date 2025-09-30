
# Tapa-Tapa Legend

## Introduction
This is a small game inspired by "Shawarma Legend".
You play as a fast-food restaurant owner, with endless delivery drivers waiting for you to provide food.
You must be fast enough, or the delivery drivers will leave with everything you gave them if they fear the order will be late.
If you successfully give all the required food to the delivery driver in time, you will earn money from the customer.
Money can be used to upgrade your microwave to heat food faster, with no upper limit.
Money can also be used to make delivery drivers wait longer, but make sure you have enough money.

## Gameplay
1. Use the mouse to drag drinks, boxed food, and bowls.
2. Drinks can be handed directly to the delivery driver.
3. Boxed food is cold, so it needs to be placed in a bowl and heated in the microwave.
4. The microwave is old and heats slowly. You can upgrade it with the money you earn. To upgrade, simply double right-click on the microwave.
5. Food taken out of the microwave can be handed directly to the delivery driver.
6. When all the delivery driver's requests are met, they will leave coins.
7. You need to manually collect coins by dragging them with the left mouse button.
8. If you don't have time to fulfill the delivery driver's requests and don't want them to leave, you can click the clock above their head. Spend 5 coins to reset their waiting time.
9. Upgrading the microwave costs 20 coins each time.
10. Good luck!

## Build

You can refer to [here](.github/workflows/build.yml) for building instructions.

## Dependencies
- SDL2
- SDL2-image
- SDL2-mixer
- SDL2-ttf

## Configuration File
This program has comprehensive configuration file support. You can customize many aspects by editing the config file.
If you find the game too difficult, you can increase the `deliveryDriver.waitTime` value, but please ensure the format is correct.

## AI Usage
This project uses minimal AI completion.
AI was used to translate the README.
