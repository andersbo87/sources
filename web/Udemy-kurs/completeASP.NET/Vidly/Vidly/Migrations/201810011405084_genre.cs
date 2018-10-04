namespace WebApplication2.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class genre : DbMigration
    {
        public override void Up()
        {
            Sql("INSERT INTO Genres (id, genereName) VALUES(1, 'Action')");
            Sql("INSERT INTO Genres (id, genereName) VALUES(2, 'Thriller')");
            Sql("INSERT INTO Genres (id, genereName) VALUES(3, 'Family')");
            Sql("INSERT INTO Genres (id, genereName) VALUES(4, 'Romance')");
            Sql("INSERT INTO Genres (id, genereName) VALUES(5, 'Comedy')");
        }
        
        public override void Down()
        {
        }
    }
}
