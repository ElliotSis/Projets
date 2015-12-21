﻿using UnityEngine;
using UnityEngine.UI;
using System.Collections.Generic;
using System.Collections;

public class RaceManager : MonoBehaviour 
{


	[SerializeField]
	private GameObject _carContainer;

	[SerializeField]
	private Text _announcement;
	
	[SerializeField]
	private PathIndicator _pathIndicator;

	[SerializeField]
	private int _timeToStart;

	[SerializeField]
	private int _endCountdown;

	[SerializeField]
	private GameInfoTransmitter gameInfo;

	[SerializeField]
	private CheckpointManager checkpointManager;

	// Use this for initialization
	void Awake () 
	{
		CarActivation(false);

	}
	
	void Start()
	{
		StartCoroutine(StartCountdown());
	}

	IEnumerator StartCountdown()
	{
		int count = _timeToStart;
		do 
		{
			_announcement.text = count.ToString();
			yield return new WaitForSeconds(1.0f);
			count--;
		}
		while (count > 0);
		_announcement.text = "Partez!";
		CarActivation(true);
		gameInfo.StartTimer ();
		yield return new WaitForSeconds(1.0f);
		_announcement.text = "";
	}

	public void EndRace(string winner)
	{
		StartCoroutine(EndRaceImpl(winner));
	}

	IEnumerator EndRaceImpl(string winner)
	{
		CarActivation(false);
		gameInfo.StopTimer ();

		foreach (KeyValuePair<CarController, CheckpointManager.PositionData> pair in checkpointManager.CarPositions) {
			gameInfo.classement[pair.Value.position - 1] = pair.Key.name;
		}

//		_announcement.fontSize = 20;
//		int count = _endCountdown;
//		do 
//		{
//			_announcement.text = "Victoire: " + winner + " en premiere place. Retour au titre dans " + count.ToString();
			yield return new WaitForSeconds(1.0f);
//			count--;
//		}
//		while (count > 0);
//

		Application.LoadLevel("end");
	}

	public void Announce(string announcement, float duration = 2.0f)
	{
		StartCoroutine(AnnounceImpl(announcement,duration));
	}
	
	public void DisplayDirection(string direction)
	{
		_pathIndicator.Display(direction);
	}

	IEnumerator AnnounceImpl(string announcement, float duration)
	{
		_announcement.text = announcement;
		yield return new WaitForSeconds(duration);
		_announcement.text = "";
	}

	public void CarActivation(bool activate)
	{
		foreach (CarAIControl car in _carContainer.GetComponentsInChildren<CarAIControl>(true))
		{
			car.enabled = activate;
		}
		
		foreach (CarUserControlMP car in _carContainer.GetComponentsInChildren<CarUserControlMP>(true))
		{
			car.enabled = activate;
		}

	}
}
