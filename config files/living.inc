define living model
(
    size [1.4 0.2 2]

    block
    (
        points 4
        point[0] [0.6 0]
        point[1] [0.6 0.2]
        point[2] [0.4 0.2]
        point[3] [0.4 0]
        z [0 0.8]
    )
    
    block
    (
        points 4
        point[0] [0.8 0]
        point[1] [0.8 0.2]
        point[2] [0.6 0.2]
        point[3] [0.6 0]
        z [0.7 2]
    )
    
    block
    (
        points 4
        point[0] [1 0]
        point[1] [1 0.2]
        point[2] [0.8 0.2]
        point[3] [0.8 0]
        z [0 0.8]
    )
    
    block
    (
        points 4
        point[0] [1.4 0]
        point[1] [1.4 0.2]
        point[2] [0 0.2]
        point[3] [0 0]
        z [1.5 1.7]
    )

        laser_return 1
        ranger_return 1	
	gripper_return 1
	fiducial_return 40
        blob_return 1
        obstacle_return 1
)
