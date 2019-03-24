# Entropy Piano Tuner

Tool for tuning Pianos and Grand Pianos with no musical knowledge.

## Information
For more information refer to the [project homepage](http://piano-tuner.org/).

## Building

### Quick instructions
The fundamental workflow to complie the Entropy Piano Tuner is the following. For further information regarding your platform have a look in the [developer pages](http://develop.piano-tuner.org).

* Install [Qt](https://www.qt.io/download-open-source/) for your platform.
* Follow the instructions of [qtmidi](https://gitlab.com/tp3/qtmidi) to build the required midi plugin.
* Clone the full repositoy including all submodules via `git clone --recursive https://gitlab.com/tp3/Entropy-Piano-Tuner.git`.
* Open the `entropypianotuner.pro` file using the QtCreator to build and run the project. Alternatively you can use `qmake` to build from the console.

## Basic Idea

The idea behind entropy-based tuning is very simple: Since entropy is a measure of disorder, we expect the entropy of a well-tuned piano to be lower than the entropy of an instrument out of tune.

For more information on entropy-based tuning, refer to [this document](http://www.sbfisica.org.br/rbef/pdf/342301.pdf).

### Developer pages
Regarding development please have a look at the [developer pages](http://develop.piano-tuner.org) for further information.
