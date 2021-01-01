using System;
using ClassLibrary1.Entity;
using Microsoft.EntityFrameworkCore;

namespace ClassLibrary1
{
    public class PlaybookContext : DbContext
    {
        public DbSet<Block> Blocks { get; set; }
        public DbSet<Playbook> Playbooks { get; set; }

        public PlaybookContext()
        {
        }

        public PlaybookContext(DbContextOptions options) : base(options)
        {
        }
    }
}