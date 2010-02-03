class InitialMigration < ActiveRecord::Migration
  def self.up
    create_table :ips do |t|
      t.string :ip
      t.integer :user_id
    end

    create_table :users do |t|
      t.string :username
      t.string :password
    end

    create_table :protocols do |t|
      t.string :protocol_name
      t.boolean :blocked
    end

    create_table :ips_protocols, :id => false do |t|
      t.integer :ip_id
      t.integer :protocol_id
    end
    create_table :users_ips, :id => false do |t|
      t.integer :user_id
      t.integer :ip_id
    end
  end

  def self.down
    drop_table :protcols
    drop_table :users
    drop_table :ips
    drop_table :ips_protocols 
    drop_table :users_ips 
  end
end

