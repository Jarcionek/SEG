define papabot_sonars ranger
(
    scount 1
    spose[0] [ 0 0 0 ]
    sview [ 0 1 360 ]
)

define papabot_laser laser
(
    range_max 10
    fov 360
    samples 181
    pose [ 0 0 -0.31 0 ]
    size [ 0.45 0.3 0.01 ]
    color "yellow"

    block
    (
        points 4
        point[0] [ -4.5 0 ]
        point[1] [ -1.5 -3 ]
        point[2] [ 4.5 0 ]
        point[3] [ -1.5 3 ]
    )
)

define papabot_fiducial fiducial
(
    range_min 0
    range_max_id 10
    range_max 10
    fov 360
    pose [ 0 0 -0.31 0 ]
    size [ 0 0 0 ]
)

define bot position (
    size [ 0.5 0.5 0.5 ]
    origin [ 0 0 0 0 ]

    block # BASE
    (
        points 12
        point[0] [ 0 5 ]
        point[1] [ -3 4 ]
        point[2] [ -4 3 ]
        point[3] [ -5 0 ]
        point[4] [ -4 -3 ]
        point[5] [ -3 -4 ]
        point[6] [ 0 -5 ]
        point[7] [ 3 -4 ]
        point[8] [ 4 -3 ]
        point[9] [ 5 0 ]
        point[10] [ 4 3 ]
        point[11] [ 3 4 ]
        color "dark green"
        z [0 0.19]
    )
    block # TOWER
    (
        points 4
        point[0] [ -1.5 0.5 ]
        point[1] [ -2.5 0.5 ]
        point[2] [ -2.5 -0.5 ]
        point[3] [ -1.5 -0.5 ]
        color "dark green"
        z [0.2 0.48]
    )
    block # BRIDGE
    (
        points 8
        point[0] [ -3.5 -0.5 ]
        point[1] [ -2.5 -1.5 ]
        point[2] [ -1.5 -1.5 ]
        point[3] [ 0.5 -0.5 ]
        point[4] [ 0.5 0.5 ]
        point[5] [ -1.5 1.5 ]
        point[6] [ -2.5 1.5 ]
        point[7] [ -3.5 0.5 ]
        color "dark green"
        z [0.43 0.49]
    )
    block # TOP
    (
        points 4
        point[0] [ -1.5 0.5 ]
        point[1] [ -2.5 0.5 ]
        point[2] [ -2.5 -0.5 ]
        point[3] [ -1.5 -0.5 ]
        color "red"
        z [0.49 0.50]
    )
    block # BASE TOP
    (
        points 4
        point[0] [ -1 0 ]
        point[1] [ 0.5 -1.5 ]
        point[2] [ 3.5 0 ]
        point[3] [ 0.5 1.5 ]
        color "red"
        z [0.2 0.21]
    )

    drive "diff"

    papabot_sonars()
    papabot_laser()
    papabot_fiducial()
)
