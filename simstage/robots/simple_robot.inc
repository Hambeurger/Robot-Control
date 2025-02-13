define laser1 ranger(
    sensor(
	range [ 0..0 5.6 ]
	fov 240.0
	samples 240
    )
    color "yellow"
    size [ 0.1 0.1 0.1 ]

    block( points 4
	point[0] [0 0]
	point[1] [0 1]
	point[2] [1 1]
	point[3] [1 0]
	z [0 1]
    )
)




define simple_robot position(


    odom_error [0.03 0.03 0.00 0.05]
    localization "odom" 
    size [ 0.4 0.3 0.4 ]

   block( points 16
        point[0] [ 0.225 0.000 ]
        point[1] [ 0.208 0.086 ]
        point[2] [ 0.159 0.159 ]
        point[3] [ 0.086 0.208 ]
        point[4] [ 0.000 0.225 ]
        point[5] [ -0.086 0.208 ]
        point[6] [ -0.159 0.159 ]
        point[7] [ -0.208 0.086 ]
        point[8] [ -0.225 0.000 ]
        point[9] [ -0.208 -0.086 ]
        point[10] [ -0.159 -0.159 ]
        point[11] [ -0.086 -0.208 ]
        point[12] [ -0.000 -0.225 ]
        point[13] [ 0.086 -0.208 ]
        point[14] [ 0.159 -0.159 ]
        point[15] [ 0.208 -0.086 ]
        z [0 1]
    )

    gui_nose 1
    drive "diff" 
    color "red"

    laser1 (pose [ 0.15 0.0 0 0])

)
