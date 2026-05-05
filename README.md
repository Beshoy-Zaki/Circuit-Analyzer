# Circuit Analyzer (C++)

A command-line C++ application to compute equivalent resistance for circuits specified in textual notation.

## Usage

This tool parses series and parallel resistor combinations and outputs the total resistance.

### Input Format

- `s<resistors>e` — series combination (e.g., `s2 3e` for 2Ω and 3Ω in series)
- `p<resistors>e` — parallel combination (e.g., `p3 6e` for 3Ω and 6Ω in parallel)
- Expressions can be nested (e.g., `s2 p3 6e e`)

### Output

- `The total resistance = <value>` on success
- `Wrong Description` if the input contains invalid characters
- `Incorrect Input` if a parallel combination has fewer than 2 resistors or a series combination has no resistors

## Compilation

```bash
g++ -std=c++11 -o circuit_analyzer circuit_analyzer.cpp
```

## Examples

```
Input:  2s3e
Output: The total resistance = 5

Input:  p3 6e
Output: The total resistance = 2
```