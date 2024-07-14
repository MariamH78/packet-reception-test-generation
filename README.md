
# packet-reception-test-generation:
Assume there is a reader instance that receives N packets from M modules i.e. module1, module2 … moduleM.

The reader instance reads from the modules in a ring-like manner, if first packet was received from module N, the next packet can only be from either module N or module N + 1, and if there’s no module N + 1, then it can be received from 1 as well. So, effectively, the only allowed senders after the first packet are module<sub>i</sub> and module<sub>i % M + 1</sub>, where i is the previous packet’s module, and M is the number of modules. Packets received that do not comply to these rules are considered invalid.

The file above generates all possible scenarios of order of receipt for some given packets, where each packet has an associated module number.

## How to run locally:

1. Clone this repository
```sh
git clone https://github.com/MariamH78/packet-reception-test-generation.git 
```
2. Build main.cpp (The command below assumes g++ exists on the machine)
```sh
g++ -o run main.cpp
```
3. Run the resulting file, and make sure to include the input file as an argument, for example:
```sh
run sample_input.txt
```

## Input formatting

The file with the input as specified in the requirements. The input must be written on one line (any other lines are ignored), with the first number being the number of packets, and the remaining numbers are the corresponding module numbers for each packet.

## Output format:

The program output requires all scenarios to be generated, so a sequence of all scenarios will be formatted like the given sample, where each scenario will consist of the sequence of rows with PacketIDs from 1 to N.

For the sample input, the output file looks like:

PacketID | ModuleNumber  | ValidModule | 
--- | --- | --- | 
1|1|Yes|
2|3|No|
3|4|Yes|
4|4|Yes|
1|1|Yes|
..|..|..|
1|4|Yes|
2|4|Yes|
3|3|No|
4|1|No|
