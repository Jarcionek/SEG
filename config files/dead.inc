define dead model
(
    size [1.4 2 0.2]

    block
    (
        points 4
        point[0] [0.6 0]
        point[1] [0.6 0.8]
        point[2] [0.4 0.8]
        point[3] [0.4 0]
        z [0 0.2]
    )
    
    block
    (
        points 4
        point[0] [0.8 0.7]
        point[1] [0.8 2]
        point[2] [0.6 2]
        point[3] [0.6 0.7]
        z [0 0.2]
    )
    
    block
    (
        points 4
        point[0] [1 0]
        point[1] [1 0.8]
        point[2] [0.8 0.8]
        point[3] [0.8 0]
        z [0 0.2]
    )
    
    block
    (
        points 4
        point[0] [1.4 1.5]
        point[1] [1.4 1.7]
        point[2] [0 1.7]
        point[3] [0 1.5]
        z [0 0.2]
    )

	laser_return 1
        ranger_return 1
	gripper_return 1
	fiducial_return 19
        blob_return 1
        obstacle_return 1
)
