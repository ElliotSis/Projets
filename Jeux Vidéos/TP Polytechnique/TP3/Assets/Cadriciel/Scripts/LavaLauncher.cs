using UnityEngine;
using System.Collections;

public class LavaLauncher : MonoBehaviour {

	[SerializeField] private GameObject lavaProjectile;
	[SerializeField] private int minForce = 100;
	[SerializeField] private int maxForce = 1000;
	[SerializeField] private float firstShoot = 3.0f;
	[SerializeField] private float timeBetweenShoot = 5.0f;
	[SerializeField] private float laveLifeTime = 15.0f;



	// Use this for initialization
	void Start () {
		StartCoroutine (LaunchCoroutine ());
	}
	
	IEnumerator LaunchCoroutine () {
		yield return new WaitForSeconds (firstShoot);
		while (true) {
			yield return new WaitForSeconds (timeBetweenShoot);

			Vector2 direction = Random.insideUnitCircle;
			int force = Random.Range(minForce, maxForce);

			Vector3 launchingForce =  new Vector3(direction.x * force, force, direction.y*force);  

			GameObject projectile = (GameObject) Instantiate(lavaProjectile, transform.position, transform.rotation);

			projectile.rigidbody.AddForce(launchingForce);
			projectile.transform.parent = transform;

			Destroy(projectile, laveLifeTime);
		}
	}
}
