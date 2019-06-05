# txn\_test\_gen\_plugin

This plugin provides a way to generate a given amount of transactions per second against the currency contract. It runs internally to bvsd to reduce overhead.

This general procedure was used when doing Dawn 3.0 performance testing as mentioned in https://github.com/BVSVC/bvs/issues/2078.

## Performance testing

The following instructions describe how to use the `txn_test_gen_plugin` plugin to generate 1,000 transaction per second load on a simple BVSVC node.

### Create config and data directories
Make an empty directory for our configs and data, `mkdir ~/bvs.data`, and define a logging.json that doesn't print debug information (which occurs for each txn) to the console:
```bash
cat << EOF > ~/bvs.data/logging.json
{
  "includes": [],
  "appenders": [{
      "name": "consoleout",
      "type": "console",
      "args": {
        "stream": "std_out",
        "level_colors": [{
            "level": "debug",
            "color": "green"
          },{
            "level": "warn",
            "color": "brown"
          },{
            "level": "error",
            "color": "red"
          }
        ]
      },
      "enabled": true
    }
  ],

  "loggers": [{
      "name": "default",
      "level": "info",
      "enabled": true,
      "additivity": false,
      "appenders": [
        "consoleout"
      ]
    }
  ]
}
EOF
```

### Launch producer
```bash
$ ./nodbvs -d ~/bvs.data/producer_node --config-dir ~/bvs.data/producer_node -l ~/bvs.data/logging.json --http-server-address "" -p bvsio -e
```

### Launch non-producer that will generate transactions
```bash
$ ./nodbvs -d ~/bvs.data/generator_node --config-dir ~/bvs.data/generator_node -l ~/bvs.data/logging.json --plugin bvsio::txn_test_gen_plugin --plugin bvsio::chain_api_plugin --p2p-peer-address localhost:9876 --p2p-listen-endpoint localhost:5555
```

### Create a wallet on the non-producer and set bios contract
```bash
$ ./clbvs wallet create --to-console
$ ./clbvs wallet import --private-key 5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3
$ ./clbvs set contract bvsio ~/bvs/build.release/contracts/bvsio.bios/
```

### Initialize the accounts txn_test_gen_plugin uses
```bash
$ curl --data-binary '["bvsio", "5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3"]' http://127.0.0.1:8888/v1/txn_test_gen/create_test_accounts
```

### Start transaction generation, this will submit 20 transactions evey 20ms (total of 1000TPS)
```bash
$ curl --data-binary '["", 20, 20]' http://127.0.0.1:8888/v1/txn_test_gen/start_generation
```

### Note the producer console prints
```bash
bvsio generated block 9b8b851d... #3219 @ 2018-04-25T16:07:47.000 with 500 trxs, lib: 3218
bvsio generated block e5b3cd5d... #3220 @ 2018-04-25T16:07:47.500 with 500 trxs, lib: 3219
bvsio generated block b243aeaa... #3221 @ 2018-04-25T16:07:48.000 with 500 trxs, lib: 3220
```

Note in the console output there are 500 transactions in each of the blocks which are produced every 500 ms yielding 1,000 transactions / second.

### Demonstration
The following video provides a demo: https://vimeo.com/266585781
