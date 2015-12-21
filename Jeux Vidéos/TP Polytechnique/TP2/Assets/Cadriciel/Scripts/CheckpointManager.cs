using UnityEngine;
using System.Collections.Generic;

public class CheckpointManager : MonoBehaviour 
{

	[SerializeField]
	private GameObject _carContainer;

	[SerializeField]
	private int _checkPointCount;
	[SerializeField]
	private int _totalLaps;

	private bool _finished = false;
	
	private Dictionary<CarController,PositionData> _carPositions = new Dictionary<CarController, PositionData>();
	private List<CarController> cars = new List<CarController>();

	public class PositionData
	{
		public int lap;
		public int checkPoint;
		public int positionCheckPoint;
		public int position;
	}
	
	public Dictionary<CarController,PositionData> CarPositions { get { return _carPositions; } }

	// Use this for initialization
	void Awake () 
	{
		foreach (CarController car in _carContainer.GetComponentsInChildren<CarController>(true))
		{
			_carPositions[car] = new PositionData();
			_carPositions[car].checkPoint = -1;
			cars.Add(car);
		}
	}

	void UpdatePositions() {
		cars.Sort(delegate(CarController x, CarController y) {
			if (_carPositions[x].lap > _carPositions[y].lap) return -1;
			else if (_carPositions[x].lap < _carPositions[y].lap) return 1;
			else if (_carPositions[x].checkPoint > _carPositions[y].checkPoint) return -1;
			else if (_carPositions[x].checkPoint < _carPositions[y].checkPoint) return 1;
			else if (_carPositions[x].positionCheckPoint < _carPositions[y].positionCheckPoint) return -1;
			else if (_carPositions[x].positionCheckPoint > _carPositions[y].positionCheckPoint) return 1;
			else return 0;
			
		});
		int i = 1;
		foreach (CarController car in cars) {
			_carPositions[car].position = i++;
		}
	}
	
	public void CheckpointTriggered(CarController car, int checkPointIndex)
	{

		PositionData carData = _carPositions[car];

		if (!_finished)
		{	
			if (checkPointIndex == 0)
			{
				if (carData.checkPoint == _checkPointCount-1)
				{
					carData.checkPoint = checkPointIndex;
					carData.lap += 1;
					Debug.Log(car.name + " lap " + carData.lap);
					if (IsPlayer(car))
					{
						GetComponent<RaceManager>().Announce("Tour " + (carData.lap+1).ToString());
					}

					if (carData.lap >= _totalLaps)
					{
						_finished = true;
						GetComponent<RaceManager>().EndRace(car.name.ToLower());
					}
				}
			}
			else if (carData.checkPoint == checkPointIndex-1) //Checkpoints must be hit in order
			{
				carData.checkPoint = checkPointIndex;
			}
			
			int positionCheckPoint = 1;
			foreach (CarController c in cars) {
				if (carData.lap == _carPositions[c].lap && carData.checkPoint == _carPositions[c].checkPoint && !NoCheckPointYet(c) && c != car) {
					positionCheckPoint++;
				}
			}
			
			carData.positionCheckPoint = positionCheckPoint;
			
			if (NoCheckPointYet(car)) {
				carData.checkPoint = 0;
			}
			
			UpdatePositions();
		}


	}
	
	bool NoCheckPointYet(CarController car) {
		PositionData d = _carPositions[car];
		return (d.checkPoint == -1);
	}

	bool IsPlayer(CarController car)
	{
		return car.GetComponent<CarUserControlMP>() != null;
	}
	
	public bool ValidPositions() {
		foreach (CarController car in cars) {
			if (NoCheckPointYet(car)) {
				return false;
			}
		}
		return true;
	}
	
	public bool IsBehind(CarController car, int position) {
		return _carPositions[car].position >  position;
	}
}
