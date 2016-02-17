# att-coref

Coreference resolution with attention mechanism

# Checking out the project for the first time

The first time you clone the repository, you need to sync the `cnn/` submodule.

    git submodule init
    git submodule update

# Build instructions

    mkdir build
    cd build
    cmake -DEIGEN3_INCLUDE_DIR=/opt/tools/eigen-dev ..
    (in allegro: cmake -DEIGEN3_INCLUDE_DIR=/opt/tools/eigen-dev -G 'Unix Makefiles')
    make -j2


Getting the data:

```
cd att-coref/data/conll-2012
gzip -d *
cd ../../coref/
```

    
# Command to run the system: 

    ./att-coref

# Update cnn instructions
To sync the most recent version of `cnn`, you need to issue the following command:
 
    git submodule foreach git pull origin master
    
    





