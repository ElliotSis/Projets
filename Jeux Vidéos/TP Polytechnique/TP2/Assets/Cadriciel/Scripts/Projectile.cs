using UnityEngine;
using System.Collections;
using System;

public class Projectile : MonoBehaviour {

	[SerializeField] string carsName = "Cars";
	[SerializeField] string terrainName = "Terrain";
	[SerializeField] float explosionForce;
	[SerializeField] float explosionRadius;
	[SerializeField] int maxBounceNb = 3;
	int cptBounce = 0;

	[SerializeField] float speed = 60f;

	public enum ProjectileType{green, red, blue};

	[SerializeField] ProjectileType type;
	[SerializeField] float maxAngle = 60f;
	[SerializeField] float maxDistance = 200f;
	[SerializeField] string playerGameObjectName = "Joueur 1";

	GameObject cars;
	GameObject terrain;

	bool collides = false;
	Transform target;

	void Awake() {
		cars = GameObject.Find (carsName);
		terrain = GameObject.Find (terrainName);
		StartCoroutine (CheckOnTerrain ());

		if (type == ProjectileType.red) {
			float minDotProduct = Mathf.Cos (maxAngle * Mathf.Deg2Rad);
			float targetDistanceSqrd = maxDistance * maxDistance;
			
			foreach (Transform car in cars.transform) {
				Vector3 relativePosition = car.position - transform.position;
				
				if (maxAngle < 90f && Vector3.Dot (relativePosition, transform.forward) <= 0f)
					continue; 
				
				float distanceSqrd = relativePosition.sqrMagnitude;
				if ((distanceSqrd < targetDistanceSqrd) &&
					(Vector3.Dot (relativePosition.normalized, transform.forward) > minDotProduct)) {
					targetDistanceSqrd = distanceSqrd;
					Debug.Log ("target is " + car.name);
					target = car;
				}
			}

			if (target == null)
				Destroy (this.gameObject);
		}
		else if (type == ProjectileType.blue) {
			foreach (Collider col in GameObject.Find(playerGameObjectName).GetComponentsInChildren<Collider>())
				Physics.IgnoreCollision(collider, col);
		}
	}

	void OnCollisionEnter(Collision other) {
		if (type != ProjectileType.blue) {
			if (cars != null) 
				foreach (Transform car in cars.transform)
					try {
						if (other.collider.attachedRigidbody.gameObject.transform == car) {
							other.collider.attachedRigidbody.AddExplosionForce (explosionForce, transform.position, explosionRadius);
							Destroy (this.gameObject);
							return;
						} 
					} catch (NullReferenceException e) {
					}

		}

		if (other.collider.gameObject.tag == "Wall") {
			if (++cptBounce > maxBounceNb) 
				Destroy (this.gameObject);
		} else 	
			Ground ();

		collides = true;
	}

	void FixedUpdate() {
		collides = false;
	}

	void Update() {
		if (!collides) {
			Ground ();

			switch (type) {
			case ProjectileType.green:
				if(rigidbody.velocity != Vector3.zero)
					transform.forward = rigidbody.velocity.normalized;
				rigidbody.velocity = speed * transform.forward;
				break;
			case ProjectileType.blue:
				target = GetComponent<WaypointProgressTracker>().target;
				transform.LookAt(target.position);
				rigidbody.velocity = speed * transform.forward;
				break;
			case ProjectileType.red:
				transform.LookAt(target.position);
				rigidbody.velocity = speed * transform.forward;
				break;
			default:
				break;
			}
		}
	}
		
	void Ground () {

		RaycastHit hit;
		if (Physics.Raycast (transform.position + Vector3.up * 5, Vector3.down, out hit)) {
			float distanceToGround = hit.distance;
			Vector3 position = hit.point;
			position.y += 0.5f;
			transform.position = position;
		}
	}


	/**
	 * 	Check if the projectile is on the terrain
	**/
	IEnumerator CheckOnTerrain() {
		while (true) {
			bool onTerrain = false;
			// For each collider of the terrain, check if the projectile is on the collider. 
			foreach (Collider col in terrain.GetComponentsInChildren<Collider>()) {
				Vector3 closest = col.ClosestPointOnBounds(transform.position);
				if(closest.x == transform.position.x && closest.z == transform.position.z)
					onTerrain = true;
				yield return null;
			}

			// If the projectile is not on any collider, destroys the projectile
			if(!onTerrain)
				Destroy(this.gameObject);
		}
	}
}
