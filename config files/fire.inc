define fire model
(
       size [1 1 1.5]

       block
       (
	    points 3
            point[0] [0.0  0.0]
            point[1] [0.4 -0.1]
            point[2] [0.4  0.1]
            z [0 1.5]
       )
       block
       (
            points 3
            point[0] [0.4 -0.1]
            point[1] [0.5 -0.5]
            point[2] [0.6 -0.1]
            z [0 1.5]
       )
       block
       (
	    points 3
            point[0] [0.6 -0.1]
            point[1] [1    0]
            point[2] [0.6  0.1]
            z [0 1.5]
       )
       block
       (
            points 3
            point[0] [0.6  0.1]
            point[1] [0.5  0.5]
            point[2] [0.4  0.1]
            z [0 1.5]
       )      
       block
       (
            points 4
            point[0] [0.4  0.1]
            point[1] [0.4 -0.1]
            point[2] [0.6 -0.1]
            point[3] [0.6  0.1]
            z [0 1.5]
       )        


	color "orange"
        laser_return 1
        ranger_return 1
	gripper_return 0
	fiducial_return 105
        blob_return 1
        obstacle_return 1
)

