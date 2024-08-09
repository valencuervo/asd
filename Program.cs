class Cuentabancaria
{
    private string _titular;
    private decimal _salario;

    public Cuentabancaria(string titular, decimal salario)
    {
        _titular = titular;
        _salario = salario;
    }

    public string Titular
    {
        get { return _titular; }
        set { _titular = value; }
    }
    public decimal Salario
    {
        get { return _salario; }
        set { _salario = value; }
    }

    public void Depositar(decimal cantidad)
    {
        if (cantidad > 0)
        {
            Salario += cantidad;
            Console.WriteLine($"deposito exitoso. \nSaldo actual : {Salario}");
        }
        else
        {
            Console.WriteLine("no podes depositar menos que 0");
        }
    }
    public void Retirar(decimal cantidad)
    {
        if (cantidad >= 1 && cantidad <= Salario)
        {
            Salario -= cantidad;
            Console.WriteLine($"retiro exitoso. \ncantidad retirada : {cantidad} \nsaldo actual: {Salario}");
        }
        else
        {
            Console.WriteLine("rataaaa");
        }
    }
}



class program
{
    static void Main()
    {
        Cuentabancaria unaCuenta = new Cuentabancaria("pepita", 1000);
        unaCuenta.Depositar(300);
        unaCuenta.Retirar(150);

        Console.WriteLine($"saldo final: {unaCuenta.Salario} ");

    }
}

