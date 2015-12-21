using UnityEngine;
using System.Collections;

public class Shooter : MonoBehaviour {
	[SerializeField] GameObject green_projectile;
	[SerializeField] GameObject red_projectile;
	[SerializeField] GameObject blue_projectile;

	GameObject currentProjectile;

	void Awake () {
		currentProjectile = null;
	}

	// Update is called once per frame
	public void shoot () {
		if (currentProjectile == null)
			return;

		Vector3 startPoint = transform.position;

		startPoint += transform.forward * 5;
		startPoint += transform.up;

		GameObject projectile = (GameObject) Instantiate(currentProjectile, startPoint, transform.rotation);

		projectile.transform.forward = transform.forward;
		currentProjectile = null;
	}

	public void switchProjectile() {
		if (currentProjectile == green_projectile)
			currentProjectile = red_projectile;
		else if (currentProjectile == red_projectile) 
			currentProjectile = blue_projectile;
		else 
			currentProjectile = green_projectile;
	}

	public void setProjectile(GameObject proj){
		currentProjectile = proj;
	}

	public string GetColor(){
		if (currentProjectile == green_projectile)
			return "Green";
		if (currentProjectile == red_projectile)
			return "Red";
		if (currentProjectile == blue_projectile)
			return "Blue";
		return "Null";
	}
}
