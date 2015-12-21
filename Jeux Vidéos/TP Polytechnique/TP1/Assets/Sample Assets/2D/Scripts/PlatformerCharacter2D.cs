using UnityEngine;
using System.Collections;

[RequireComponent(typeof(Platformer2DUserControl))]
public class PlatformerCharacter2D : MonoBehaviour 
{
	// Flags, counters…
	bool facingRight = true;							// For determining which way the player is currently facing.
	uint jumpCounter = 0;								// For determining the number of jumps in the air the player already made.
	float jetpackFuel = 0;								// For determining the amount of fuel left in the jetpack.

	// Serialized fields
	[SerializeField] float maxSpeed = 10f;				// The fastest the player can travel in the x axis.
	[SerializeField] float jumpForce = 80f;				// Amount of force added over time when the player jumps.	
	[SerializeField] float jumpTime = 0.5f; 			// Maximum time you can hold the jump button to jump higher.
	[SerializeField] int maxJumps = 2;					// Maximum number of jumps the player can make without touching the ground.
	[SerializeField] bool showMaxJumpHeight;			// DEBUG : If true, shows a line that indicates the maximum height of the jump.

	[SerializeField] float wallJumpForce = 800f;		// Amount of force added diagonally when the player jumps from a wall.	
	[SerializeField] float wallJumpTime = 0.1f;			// Time it takes to bounce off the wall (the horizontal input is disabled during that time).	

	[SerializeField] float jetpackForce = 15f;			// Amount of force added over time when the player uses the jetpack.
	[SerializeField] float maxJetpackFuel = 4f;			// Maximum fuel of the jetpack (i.e. the time it is possible to use the jetpack).
	[SerializeField] float rechargeFuelMultiplier = 2f;	// Multiplier to recharge the jetpack faster.

	[Range(0, 1)]
	[SerializeField] float crouchSpeed = .35f;			// Amount of maxSpeed applied to crouching movement. 1 = 100%
	[Range(0, 1)]
	[SerializeField] float airControl = .65f;			// Amount of maxSpeed applied to the horizontal movement while the player is in the air. 1 = 100%

	[SerializeField] LayerMask whatIsGround;			// A mask determining what is ground to the character.
	[SerializeField] LayerMask whatIsWall;				// A mask determining what is wall to the character.

	// References, collisions, animation…
	Transform groundCheck;								// A position marking where to check if the player is grounded.
	float groundedRadius = .2f;							// Radius of the overlap circle to determine if grounded.
	bool grounded = false;								// Whether or not the player is grounded.
	Transform ceilingCheck;								// A position marking where to check for ceilings
	float ceilingRadius = .01f;							// Radius of the overlap circle to determine if the player can stand up
	Transform wallCheck;								// A position marking where to check if the player is against a wall.
	bool againstWall = false;							// Whether or not the player is against a wall.
	float wallRadius = .2f;								// Radius of the overlap circle to determine if the player is against a wall.
	Animator anim;										// Reference to the player's animator component.
	Platformer2DUserControl userControl;				// Reference to the player's control component.

	void Awake()
	{
		// Setting up references.
		groundCheck = transform.Find("GroundCheck");
		wallCheck = transform.Find("WallCheck");
		ceilingCheck = transform.Find("CeilingCheck");
		anim = GetComponent<Animator>();
		userControl = GetComponent<Platformer2DUserControl> ();

		// Setting up values.
		jetpackFuel = maxJetpackFuel;
	}

	void OnValidate() {
		// Checking values.
		if (maxJumps < 0) {
			Debug.Log ("<color=red>Warning:</color> The number of jumps the player can make in the air must be positive ! Setting it to its initial value (which is 2)…");
			maxJumps = 2;
		}
		if (jumpTime < 0f) {
			Debug.Log("<color=red>Warning:</color> The time during which the player can jump must be positive ! Setting it to its initial value (which is 0.5 seconds)…");
			jumpTime = 0.5f;
		}
		// etc.
	}

	void FixedUpdate()
	{
		if (showMaxJumpHeight) {
			// Estimating the maximum jump height.
			float maxJumpHeight = jumpTime * jumpTime * ((jumpForce / (3 * rigidbody2D.mass)) + (Physics2D.gravity.y / 2));

			// Looking for collisions…
			RaycastHit2D hit = Physics2D.Raycast(transform.position, new Vector2(0, 1), maxJumpHeight, whatIsGround.value);
			if (hit.collider != null) {
				Debug.DrawLine (new Vector3 (transform.position.x, transform.position.y, 0), new Vector3 (transform.position.x, hit.transform.position.y, 0), Color.red);
			}
			else {
				Debug.DrawLine (new Vector3 (transform.position.x, transform.position.y, 0), new Vector3 (transform.position.x, transform.position.y + maxJumpHeight, 0), Color.red);
			}
		}

		// The player is grounded if a circlecast to the groundcheck position hits anything designated as ground
		grounded = Physics2D.OverlapCircle(groundCheck.position, groundedRadius, whatIsGround);
		anim.SetBool("Ground", grounded);

		// The player is against a wall if a circlecast to the wallcheck position hits anything designated as wall
		againstWall = Physics2D.OverlapCircle(wallCheck.position, wallRadius, whatIsWall);

		// Set the vertical animation
		anim.SetFloat("vSpeed", rigidbody2D.velocity.y);

	}


	public void Move(float move, bool crouch, bool jump)
	{


		// If crouching, check to see if the character can stand up
		if(!crouch && anim.GetBool("Crouch"))
		{
			// If the character has a ceiling preventing them from standing up, keep them crouching
			if( Physics2D.OverlapCircle(ceilingCheck.position, ceilingRadius, whatIsGround))
				crouch = true;
		}

		// Set whether or not the character is crouching in the animator
		anim.SetBool("Crouch", crouch);

		//only control the player if grounded or airControl is turned on
		if(grounded || airControl > 0f)
		{
			// Reduce the speed if crouching by the crouchSpeed multiplier
			move = (crouch ? move * crouchSpeed : move);

			// Reduce the speed if the player is in the air by the airControl multiplier
			move = (grounded ? move : move * airControl);

			// The Speed animator parameter is set to the absolute value of the horizontal input.
			anim.SetFloat("Speed", Mathf.Abs(move));

			// Move the character
			rigidbody2D.velocity = new Vector2(move * maxSpeed, rigidbody2D.velocity.y);
			
			// If the input is moving the player right and the player is facing left...
			if(move > 0 && !facingRight)
				// ... flip the player.
				Flip();
			// Otherwise if the input is moving the player left and the player is facing right...
			else if(move < 0 && facingRight)
				// ... flip the player.
				Flip();
		}

		// If the player is not in the air
		if (grounded) {
			// Reset the jump counter
			jumpCounter = 0;
			// Recharge jetpack
			jetpackFuel = Mathf.Min(jetpackFuel + (Time.fixedDeltaTime * rechargeFuelMultiplier), maxJetpackFuel);
		}

		// If the player should jump...
		if (jump) {
			if (againstWall) {
				// Start jumping againt the wall
				// NOTE : considering the placement of the wall check, the only way to jump against a wall is to be facing it.
				// This behaviour is wanted as it wouldn't make much sense not to be facing the wall in that situation.
				StartCoroutine ("WallJumpCoroutine");
			}
			else if(jumpCounter < maxJumps) {
				// Start jumping.
				StartCoroutine ("JumpCoroutine");

			}
			else {
				// Start using the jetpack.
				StartCoroutine("JetpackCoroutine");
			}
		}
	}

	IEnumerator JumpCoroutine(){
		float timer = 0f;

		anim.SetBool ("Ground", false);
		rigidbody2D.velocity = Vector2.zero;

		while (timer < jumpTime && userControl.JumpButtonPressed()) {
			float proportionCompleted = timer / jumpTime;
			rigidbody2D.AddForce(Vector2.Lerp(new Vector2(0f, jumpForce), Vector2.zero, proportionCompleted));
			timer += Time.fixedDeltaTime; 
			yield return new WaitForFixedUpdate();
		}

		jumpCounter++;
	}

	IEnumerator WallJumpCoroutine(){
		float tmp = airControl;

		anim.SetBool ("Ground", false);

		// Jumping off the wall
		rigidbody2D.AddForce (new Vector2((facingRight) ? -wallJumpForce : wallJumpForce, wallJumpForce));
		// Flipping the player
		Flip();

		// Disable the horizontal input while jumping to make sure the player bounces off the wall despite of the input
		airControl = 0f;
		yield return new WaitForSeconds(wallJumpTime);
		airControl = tmp;
	}

	IEnumerator JetpackCoroutine() {
		anim.SetBool ("Ground", false);

		rigidbody2D.velocity = Vector2.zero;

		while(jetpackFuel > 0f && !grounded && userControl.JumpButtonPressed()) {
			rigidbody2D.AddForce(new Vector2(0, jetpackForce));
			jetpackFuel -= Time.fixedDeltaTime;
			yield return new WaitForFixedUpdate();
		}
	}

	void Flip ()
	{
		// Switch the way the player is labelled as facing.
		facingRight = !facingRight;
		
		// Multiply the player's x local scale by -1.
		Vector3 theScale = transform.localScale;
		theScale.x *= -1;
		transform.localScale = theScale;
	}

	// Returns true if the player is grounded
	public bool isGrounded(){
		return grounded;
	}

	// Returns true if the player can only use the jetpack (ie. no more multiple jumps remaining)
	public bool onJetpack(){
		return (jumpCounter == maxJumps);
	}
}
