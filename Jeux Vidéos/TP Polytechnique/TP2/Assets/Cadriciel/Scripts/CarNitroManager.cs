using UnityEngine;
using System.Collections;

public class CarNitroManager : MonoBehaviour {						
	[SerializeField] private float maxNitro = 10f;									// The maximum nitro that the car can have
	[SerializeField] float nitroAddedPerSecond = 1.0f;								// The nitro fuel added every second
	[SerializeField] float nitroScoreIncrease = 0.1f;								// The percentage of the score increase that will fuel the nitro
	[SerializeField] float nitroConsumed = 0.2f;									// The nitro consumed when used
	
	private bool isRefueling = false;												// Whether or not the car is refueling
	private float previousScore = 0.0f;												// The previous score of the car
	private CarScoreManager carScore;												// The car's score	
	
	public float Nitro {get; private set;}											// The car's actual nitro fuel
	
	public delegate void Consummed();
	public Consummed consummed; // Triggers when nitro is consummed.
	
	public float MaxNitro {
		get { return maxNitro; }
	}
	
	void Awake() {
		Nitro = 0.0f;
		carScore = GetComponent<CarScoreManager>();
	}
	
	void Update() {
		if (Nitro < maxNitro && !isRefueling) {
			StartCoroutine("RefillNitro");
		}
		if (carScore.Score > previousScore) {
			AddNitro ((carScore.Score - previousScore)*nitroScoreIncrease);
			previousScore = carScore.Score;
		}
		
	}
	
	IEnumerator RefillNitro() {
		isRefueling = true;
		yield return new WaitForSeconds(1.0f);
		AddNitro (nitroAddedPerSecond);
		isRefueling = false;
	}
	
	public void AddNitro(float amount) {
		if (Nitro + amount < maxNitro) {
			Nitro += amount;
		}
		else if (Nitro < maxNitro) {
			Nitro = maxNitro;
		}
	}
	
	public void ConsumeNitro() {
		if (Nitro - nitroConsumed >= 0) {
			if (consummed != null) {
				consummed();
			}
			Nitro -= nitroConsumed;
		}
		else {
			Nitro = 0.0f;
		}
	}
	
	
}
