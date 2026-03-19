[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=23170704)
# chooseYourOwnAdventure
a game for cpsc-25 

Richy - Added the player class. Implemented a system with stats such as health, money and luck that tracks the status of the player

    Feature 1: Dynamic Status Tracking. Implemented a health-based condition system that labels the player as "Healthy" or "Wounded," affecting the console UI.

    Feature 2: Survivor Scaling. Added a "Luck" attribute that increases the longer a player survives without dying, which scales to mitigate damage from traps.

    Function 1: displayPlayerReport – A UI-specific function in main that monitors health thresholds and issues "Near Death" warnings to the player.

    Function 2: handleSurvivalBonus – A logic function in main that tracks consecutive actions and rewards the player with stat boosts every 3 turns.

Esteban - Added the item system 

    Feature 3: Item Metadata. Expanded the Item class to include rarity (Common/Rare/Legendary) and weight, moving beyond simple strings.

    Feature 4: Single-Loot Logic. Integrated a searched state within the Room to ensure items can only be scavenged once, preventing infinite farming.

    Function 3: processLoot – A robust function in main that manages the transfer of Item objects from a Room node to the Player inventory.

    Function 4: getItemFlavorText – A utility function in main that generates unique descriptive strings for items to increase immersion.

Andreas - added the random event system 

    Feature 5: Attrition Engine. Developed a biased random event system inspired by "60 Seconds," where every choice has a randomized range of health loss or gold gain.

    Feature 6: Luck Mitigation. Integrated a "Luck" check that allows the player to automatically dodge or reduce the damage of negative events based on their stats.

    Function 5: executeEvent – A wrapper function in main that triggers the random logic and handles the narrative output to the console.

    Function 6: checkEventSafety – A pre-event calculation function in main that compares player stats against event difficulty to determine if an event is avoided.