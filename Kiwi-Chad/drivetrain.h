class DriveTrain {
  private:
    double velocity;

  public:
    DriveTrain();
    double ReturnVelocity();
    void IncreaseVelocity();
    void DecreaseVelocity();
    void SetVelocity(double newVel);

    void Drive(double hVel, double vVel);
};