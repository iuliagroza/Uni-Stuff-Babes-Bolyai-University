# 🚕 Simulator
Write a console-based, object-oriented Python application to help organize a taxicab dispatch for a city. City locations are provided in `(x,y)` format, with `0 <= x,y <= 100` (e.g. `(0,0)`, `(5,60)`, `(98,98)` are all valid locations -- `x`,`y` are integers for simplicity). Implement the following functionalities:
1. When starting the program, the user provides the number of operational taxis (between 0 and 10). The program generates the required number of **Taxi** instances at random, but valid `(x,y)` coordinates; distance between any two taxis must be `>5`. Each Taxi has a unique `ID` and starts with `0` total fare. Use the [Manhattan distance](https://xlinux.nist.gov/dads/HTML/manhattanDistance.html) in your implementation (e.g. distance between `(80,80)` and `(90,90)` is 20) **[2p]**.
2. Add a **Ride**. The user enters the start point and end point using `(x,y)` coordinate pairs (e.g. from `(10,10)` to `(25,18)`). The program will:
- Assign the **Taxi** closest to the start point with the ride (use the Manhattan distance).
- The Taxi's total fare is increased by the distance (e.g. the Manhattan distance between `(10,10)` and `(25,18)` is `23`).
- Place the Taxi at the end point of the ride **[2p]**.
3. Simulate rides. The user enters a positive integer. The program will simulate that number of rides by:
- Generating random, but valid start and end coordinates for each ride. The length of each ride must be at least `10`, according to the Manhattan distance.
- Assigning the closest Taxi, increasing its total fare and moving it to the end point of the ride.
- After each ride, printing out the ride's details (Taxi ID, start and end location) **[2p]**.
4. After each operation, the program displays the situation of the taxis, including their ID's ([left justified](https://www.tutorialspoint.com/python/string_ljust.htm)), current location and total fare (both [right justified](https://www.tutorialspoint.com/python/string_rjust.htm)), sorted in decreasing order of total fare. This also happens after each simulated ride **[2p]**.
## Non-functional requirement
* PyUnit test case and specification for functionality 2 (adding a ride) **[1p]**

## default 1p

## Example:
- Let's say we want to generate 3 taxis. They could have ID's #1, #2 and #3, with coordinates (10,10), (50,50), (100,100), respectively. They each start with 0 fare.
- We add a ride from (40,40) to (90,90), so a distance of 100.
- Closest Taxi is #2 at (50,50), so it is assigned the ride.
- When the ride is complete, Taxi #2 is located at (90,90) and its total fare is now 100. 
- The program displays the situation of the taxis as required at (4).
