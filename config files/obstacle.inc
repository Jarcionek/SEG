define obstacle model
(
    size [2 0.75 0.6]

    block
    (
        points 4
        point[0] [0 0]
        point[1] [2 0]
        point[2] [2 0.75]
        point[3] [0 0.75]
        z [0 0.6]
    )

    laser_return 1
    ranger_return 1
    gripper_return 1
    blob_return 1
    obstacle_return 1
)

