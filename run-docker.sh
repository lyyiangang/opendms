xhost +local:${USER}
docker run -it --rm     \
    -e DISPLAY=$DISPLAY     \
    -v /tmp/.X11-unix:/tmp/.X11-unix     \
    -u $(id -u):$(id -g) \
    -v ${PWD}:${PWD} \
    -w ${PWD} \
    --name opendms \
    opendms