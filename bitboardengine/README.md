# Chess bitboard Engine

## Overview

This is a custom chess engine written in **C** that uses **bitboards** for representing piece positions and **NNUE** (Efficiently Updatable Neural Networks) for position evaluation. The engine is **not UCI-compliant**, and it uses a custom command interface for interaction and gameplay. It is designed for high performance, utilizing bitboards for efficient move generation and an NNUE network to evaluate chess positions for strategic decision-making.

## Features

- **Bitboard Representation**: Uses 64-bit integers (bitboards) to represent the board state, which allows for efficient move generation and board manipulation.
- **NNUE Evaluation**: Leverages an NNUE network to evaluate chess positions, resulting in stronger strategic play.
- **Fast Move Generation**: Efficiently generates all legal moves, including handling special cases such as castling, en passant, and pawn promotion.
- **Alpha-Beta Search**: Uses Alpha-Beta pruning for searching the best move up to a specified depth.
- **Supports Full Chess Rules**: Implements all standard rules of chess, including draw conditions, promotion, and castling rights.

## Requirements

- A C compiler (GCC, Clang, etc.)
- In HowToCompile.md we will find a ompiler flags (Write in whather build system you want.)
- Basic understanding of bitboards and chess rules

## Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/BlagojeBlagojevic/chess/
    ```

2. Navigate to the project directory:

    ```bash
    cd chess
    ```

3. Build the project using whatever:
  Ther are two diferent c files:
    1. main.c -> When this file is compiled we get ability to play a game versus the engine.
    2. testmain.c -> This c file is compiled for testing purposes of testing(Engine plays versus himself).
  




## Limitations

- **Non-UCI Compliant**: The engine doesn't implement the Universal Chess Interface (UCI), so it cannot be used directly with UCI-based chess GUIs.
- **Evaluation Depends on NNUE**: The engine’s strength is closely tied to the quality of the NNUE weights(Ther is a custom evaluation functions(Around 800 - 900 ELO
- to used it coment out `#define NNUE` in main file.)).

## Future Improvements

- Add UCI compatibility for broader compatibility with popular chess GUIs.
- Add prefit driver
- Improve search algorithms by incorporating more advanced techniques like iterative deepening and principal variation search.
- Further optimize NNUE integration for better evaluation speed and accuracy.

## Contributing

Contributions are welcome! If you’d like to improve the engine, optimize performance, or add new features, feel free to submit a pull request. Please fork the repository, make your changes, and submit a pull request with a detailed explanation.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more information.

---

Enjoy using and contributing to the chess engine! Feel free to open issues or reach out with feedback and suggestions.
