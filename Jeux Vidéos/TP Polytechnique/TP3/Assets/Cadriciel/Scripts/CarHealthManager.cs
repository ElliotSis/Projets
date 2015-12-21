using UnityEngine;
using System.Collections;

public class CarHealthManager : MonoBehaviour {							
	[SerializeField] private float maxHealth = 10f;									// The maximum health that the car can have
	[SerializeField] private float damageLost = 0.8f;								// The health lost when damaged
	
	// Delegate that triggers when the player is dead
	public delegate void Die();
	public Die die;
	
	// Delegate that triggers when the player is losing health
	public delegate void HealthLoss();
	public HealthLoss healthLoss;
	
	public float Health {get; private set;}											// The car's actual health
	
	public float MaxHealth {
		get { return maxHealth; }
	}
	
	void Awake() {
		Health = maxHealth;
	}
	
	public void Damage() {
		ConsumeHealth(damageLost);
	}
	
	void ConsumeHealth(float healthConsumed) {
		if (Health - healthConsumed < 0f) {
			Health = 0f;
			if(die != null) {
				die(); // Trigger die
			}
		}
		else {
			Health -= healthConsumed;
		}
		
		if(healthLoss != null) {
			healthLoss(); // Trigger health loss
		}
	}

	public void ResetHealth ()
	{
		Health = maxHealth;
	}

}
