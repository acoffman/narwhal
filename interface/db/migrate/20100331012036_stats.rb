class Stats < ActiveRecord::Migration
  def self.up
    create_table :stats do |t|
      t.timestamp :created_at
      t.integer :numPackets
      t.integer :numDroppedPackets
      t.integer :totalData
    end
  end

  def self.down
    drop_table :stats
  end
end
