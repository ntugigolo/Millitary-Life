# Search-and-Rescue

## Generate the simulation path of victim at sea.

### SAR is the computing program which will generate the simulation result. It composed by seven classes. These classes and their corresponding function are:

1.	PathGenerator: Implement the algorithm for path simulation.
2.	CurrentMap: Implement the algorithm for path simulation.
3.	WindMap: Implement the algorithm for path simulation.
4.	CoeffHandler: Setting the parameters.
5.	Vec2D: Implement data structure.
6.	Grid: Implement data structure.
7.	Number: Numerical processing.

![screenshot](https://github.com/ntugigolo/Search-and-Rescue/edit/master/Picture/Architecture.png)

The above picture shows the architecture of SAR program. 
The single solid line represents command, triple solid line represents single-directional data transportation, double dotted line represents mutual directional data transportation.

![screenshot](https://github.com/ntugigolo/Search-and-Rescue/edit/master/Picture/Current_Wund_Map.png)

The above picture shows the architecture of CurrentMap and WindMap class. 
The single solid line represents command, triple solid line represents single-directional data transportation, double dotted line represents mutual directional data transportation.

![screenshot](https://github.com/ntugigolo/Search-and-Rescue/edit/master/Picture/Pathgenerator.png)

The above picture shows the architecture of PathGenerator class. 
The single solid line represents command, triple solid line represents single-directional data transportation, double dotted line represents mutual directional data transportation.
