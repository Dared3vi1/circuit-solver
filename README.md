# Circuit solver

## Program goal

Find all currents of a circuit consisting of resistors and voltage sources

  
## Input
  The electrical circuit must be represented as a list of edges, which have one of two forms:
  1) If voltage source connected to the edge
  `<node_1> -- <node_2>, <resistance>; <voltage>V;`
  2) If no voltage source is connected to the edge
  `<node_1> -- <node_2>, <resistance>;`
    
  The example circuit is presented in the file input.txt
  
  
## Output
The answer will be printed in file `output.txt`, that will contain an answer in the following form:
`<node_1> -- <node_2>, <amperage>A;`


### Test example
The test example is the circuit, that can be found on the following link: http://myelectronix.ru/postoyannyy-tok/36-zakony-kirkhgofa-reshenie-zadach

