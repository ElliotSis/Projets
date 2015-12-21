using UnityEngine;

[RequireComponent(typeof(CarController))]
public class CarUserControlMP : MonoBehaviour
{
	private CarController car;  // the car controller we want to use
	
	[SerializeField]
	private string vertical = "Vertical";
	
	[SerializeField]
	private string horizontal = "Horizontal";
	[SerializeField]
	private string thirdAxis = "Mouse X";
	
	[SerializeField]
	private string nitro = "Fire2";
	
	[SerializeField]
	private string jump = "Jump";
	[SerializeField]
	private string fire = "Fire1";
	
	Shooter shooter;
	
	void Awake ()
	{
		// get the car controller
		car = GetComponent<CarController>();
		shooter = GetComponent<Shooter> ();
	}
	
	
	void FixedUpdate()
	{
		// pass the input to the car!
		#if CROSS_PLATFORM_INPUT
		float h = CrossPlatformInput.GetAxis(horizontal);
		float v = CrossPlatformInput.GetAxis(vertical);
		float t = CrossPlatformInput.GetAxis(thirdAxis);
		bool n = CrossPlatformInput.GetButton(nitro);
		bool j = CrossPlatformInput.GetButton(jump);
		bool firing = CrossPlatformInput.GetButton(fire);
		#else
		float h = Input.GetAxis(horizontal);
		float v = Input.GetAxis(vertical);
		float t = Input.GetAxis(thirdAxis);
		bool firing = Input.GetButton(fire);
		bool n = Input.GetButton(nitro);
		bool j = Input.GetButton(jump);
		#endif
		car.Move(h,v,t,n,j);
		if (firing) shooter.shoot();
	}
}