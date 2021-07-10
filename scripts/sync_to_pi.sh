scp -rv ../build/install_aarch64/lib firefly@192.168.50.38:/home/firefly/test/ 
scp -v ../build/demo.out firefly@192.168.50.108:/home/firefly/test/bin/
scp -v ../cfg.json firefly@192.168.50.38:/home/firefly/test/
scp -rv ../models/ firefly@192.168.50.38:/home/firefly/test/