class DashboardController < ApplicationController

  use_google_charts

def index
	overview
  render :overview
end

def edit_num
  @test_num = params[:value]
  render :text => @test_num
end

def overview
  @page_title = "Firewall Performance Overview"
  @test_num = params[:test_num]
  @test_num ||= 55
  @nav_over = "current"
  dataset5 = GoogleChartDataset.new :data => [0,100]
  dataset6 = GoogleChartDataset.new :data => [@test_num, @test_num], :color => '0000FF', :title => 'Allowable Average Rate'
  dataset3 = GoogleChartDataset.new :data => [0,100]
  dataset4 = GoogleChartDataset.new :data => [75, 75], :color => 'FF0000', :title => 'Allowable Peak Rate'
  dataset1 = GoogleChartDataset.new :data => [0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
  dataset2 = GoogleChartDataset.new :data => [10, 50, 24, 10, 26, 32, 45, 43, 23, 42, 65], :color => '000000', :title => 'Traffic'
  @chart = init_chart("Incoming Traffic Average Rates", [dataset1, dataset2, dataset3, dataset4, dataset5, dataset6])
end

def ip
  @blocked = Blocked.new
  @page_title = "IP Configuration"
  @nav_ip = "current"
  @userid = 1

  if params[:commit] == 'Add IP'
    @blocked = Blocked.create(params[:blocked])
    return redirect_to :action => 'ip'
  elsif params[:commit] == 'Delete IP'
    return redirect_to :action => 'delete'
  end
  # pull ips from database for specific user
  @list = []
  list = (Blocked.find(:all, :conditions => "userid = #@userid and ip is not null", 
                       :select => "ip", :order => "ip"))
  list.each do |l|
    @list.push(l.ip)
  end

  #pull protocols from database for specific user
  @proto = []
  proto = (Blocked.find(:all, :conditions => "userid = #@userid and ip is null",
                        :select => "protocol", :order => "protocol"))
  proto.each do |p|
    @proto.push(p.protocol)
  end

  render :ip
end

def delete
  debugger
  ip = params[:option_list]
  ip.each do |i|
    @ip = i[0]
    to_delete = Blocked.find(:all, :conditions => "userid = 1 and ip = #@ip",
                              :select => "id")
    Blocked.delete(to_delete.id)
  end
end

def new
  @blocked = Blocked.new
  @user = User.new
end

def create
@blocked = Blocked.create(params[:blocked])
render :action => "ip"
 #respond_to do |format|
  # if @blocked.save
   #  format.html { redirect_to @blocked  }
 #  else
  #   format.html { render :action => "ip" }
 #  end
 #end

 # @blocked = Blocked.new(params[:blocked])
  #@ip = params[:blocked]['ip']
  #@port = params[:blocked]['port']
  #@protocol = params[:blocked]['protocol']
  # add
 # @user = User.new(params[:user])
end

def add
  list = (Blocked.find(:all, :conditions => "userid = #@userid and ip = #@ip
                      and port = #@port and protocol = #@protocol"))
  if not list.empty?
    Blocked.create(:userid => @userid, :ip => @ip, :protocol => @protocol, :port => @port)
  end   
  ip
end

def protocols
  @page_title = "Protocol Configuration"
  @nav_proto = "current"
  render :protocols
end

def move_item
  protocol = params[:protocol].split("_")[0]
  list = params[:protocol].split("_")[1]

  render :update do |page|
    page.remove "protocol_#{protocol}"
    page.insert_html :bottom, list, render(:partial=>"protocol", :object => protocol)
    page.visual_effect :highlight, "protocol_#{protocol}"
  end

end

private
def init_chart(title, datasets)
  data = GoogleChartData.new :datasets => datasets
  axis = GoogleChartAxis.new :axis  => [GoogleChartAxis::LEFT, GoogleChartAxis::BOTTOM]
  chart = GoogleLineChart.new :chart_type => GoogleLineChart::XY , :width => 500, :height => 300, :title => title
  chart.data = data
  chart.axis = axis
  chart
end

end
