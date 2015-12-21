using UnityEngine;
using System.Collections;

public class Collectionable : MonoBehaviour {
	[SerializeField] GameObject projectile_bonus;
	[SerializeField] float bonus_nitro = 0.0f;

	void OnTriggerEnter(Collider col){
		if (col != null && col.transform.parent != null && col.transform.parent.gameObject.transform.parent != null && col.transform.parent.gameObject.transform.parent.name == "Joueur 1") {
			if(projectile_bonus == null){
				//C'est la nitro
				col.transform.parent.gameObject.transform.parent.gameObject.GetComponent<CarNitroManager>().AddNitro(bonus_nitro);
			} else {
				Shooter shooter = col.transform.parent.gameObject.transform.parent.gameObject.GetComponent<Shooter> ();
				if (shooter != null) 
					shooter.setProjectile (projectile_bonus);
			}
			Destroy (this.gameObject);
		}
	}

	void Update(){
		this.transform.Rotate (0.5f, 0.5f, 0.5f);
	}
}