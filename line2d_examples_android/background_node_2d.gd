extends Node2D

const GREEN = Color( 0, 175, 10)
const RED   = Color( 175, 0, 0)
const TAN   = Color( 122, 100, 36)

const DELAY_SECONDS = 1

var tongue

var x1
var x2
var y2

var game_loop = 0
var game_time = 0

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	var face
	var left_eye
	var right_eye
	var nose
	var mouth

		
	x1=0
	x2=0
	y2=100

#   #Calculate initial position of tongue
	x2=x1*200+400
	y2=200

		#Create then draw face
	face = Line2D.new()
	face.set_default_color( TAN )
	face.set_width(1)
	face.set_closed(true)
	face.set_global_position(Vector2(400,0))
	face.add_point(Vector2( 50, 50))
	face.add_point(Vector2( 50, 450))
	face.add_point(Vector2( 450, 450))
	face.add_point(Vector2( 450, 50))
	add_child(face)
	#face.free()
	
		#Create then draw left eye
	left_eye = Line2D.new()
	left_eye.set_default_color( GREEN )
	left_eye.set_width(1)
	left_eye.set_closed(true)
	left_eye.set_global_position(Vector2(475,25))
	left_eye.add_point(Vector2( 75, 75))
	left_eye.add_point(Vector2( 75, 100))
	left_eye.add_point(Vector2( 100, 100))
	left_eye.add_point(Vector2( 100, 75))
	add_child(left_eye)
	#left_eye.free()

	#Create then draw right eye
	right_eye = Line2D.new()
	right_eye.set_default_color( GREEN )
	right_eye.set_width(1)
	right_eye.set_closed(true)
	right_eye.set_global_position(Vector2(375, 25))
	right_eye.add_point(Vector2( 375, 75))
	right_eye.add_point(Vector2( 350, 75))
	right_eye.add_point(Vector2( 350, 100))
	right_eye.add_point(Vector2( 375, 100))
	add_child(right_eye)
	#left_eye.free()

	#Create then draw nose
	nose = Line2D.new()
	nose.set_default_color( RED )
	nose.set_width(1)
	nose.set_closed(false)
	nose.set_global_position(Vector2(400,0))
	nose.add_point(Vector2( 225, 175))
	nose.add_point(Vector2( 225, 200))
	nose.add_point(Vector2( 175, 225))
	nose.add_point(Vector2( 175, 250))
	nose.add_point(Vector2( 225, 250))
	add_child(nose)
	#nose.free()

	#Create then draw mouth
	mouth = Line2D.new()
	mouth.set_default_color( RED )
	mouth.set_width(1)
	mouth.set_closed(false)
	mouth.set_global_position(Vector2(400,0))
	mouth.add_point(Vector2( 75, 225))
	mouth.add_point(Vector2( 100, 300))
	mouth.add_point(Vector2( 400, 300))
	mouth.add_point(Vector2( 425, 225))
	add_child(mouth)
	#mouth.free()

	#Draw tongue
	tongue = $Tongue_Line2D
	tongue.set_default_color(RED)
	tongue.set_global_position(Vector2(x2,y2))
	tongue.add_point(Vector2( 100, 100))
	tongue.add_point(Vector2( 100, 200))
	tongue.add_point(Vector2( 200, 200))
	tongue.add_point(Vector2( 200, 100))
	#while true:

	pass # Replace with function body.

#Delay for N seconds.  Fractions are ok.
func wait(seconds: float) -> void:
	await get_tree().create_timer(seconds).timeout

#Delta comes from _process() and is the elapsed time since the previous frame
func move_tongue(delta: float) -> void:
	if game_loop%(60*DELAY_SECONDS) == (60*DELAY_SECONDS-1):
		x1=(x1+1)%2
		x2=x1*200+400
		y2=200
	pass

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	game_loop=game_loop+1
	game_time=game_time+delta
	move_tongue(delta)
	tongue.set_global_position(Vector2(x2,y2))		
	pass
